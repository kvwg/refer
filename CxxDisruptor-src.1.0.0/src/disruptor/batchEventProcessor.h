/*
 * Copyright 2013 Henrik Baastrup
 *
 * Licensed under GNU Lesser General Public License, Version 3 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.gnu.org/licenses/lgpl-3.0.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef BATCHEVENTPROCESSOR_H
#define BATCHEVENTPROCESSOR_H

#include <functional>
#include "eventProcessor.h"
#include "atomicBool.h"
#include "atomicInt64.h"
#include "ringBuffer.h"
#include "sequenceBarrier.h"
#include "eventHandler.h"
#include "fatalExceptionHandler.h"
#include "illegalStateException.h"
#include "alertException.h"
#include "nullPointerException.h"

namespace disruptor {

    /**
     * @brief Implements EventProcessor
     * Convenience class for handling the batching semantics of consuming entries from a RingBuffer
     * and delegating the available events to a EventHandler.
     *
     * If the EventHandler  will be notified just after the thread is started and just before the
     * thread is shutdown.
     *
     * @param <T> event implementation storing the data for sharing during exchange or parallel coordination of an event.
     */
    template<class T>
    class BatchEventProcessor : public EventProcessor
    {
    private:
        hba::atomic::AtomicBool running;
        //private ExceptionHandler exceptionHandler = new FatalExceptionHandler();
        RingBuffer<T> *ringBuffer;
        SequenceBarrier *sequenceBarrier;
        EventHandler<T> *eventHandler;
        hba::atomic::AtomicInt64 sequence;
        ExceptionHandler *exceptionHandler;


    public:
        BatchEventProcessor(RingBuffer<T> *ringBuffer, SequenceBarrier *sequenceBarrier, EventHandler<T> *eventHandler) : running(false), sequence(hba::atomic::AtomicInt64::INITIAL_CURSOR_VALUE)
        {
            this->ringBuffer = ringBuffer;
            this->sequenceBarrier = sequenceBarrier;
            this->eventHandler = eventHandler;
            this->exceptionHandler = new FatalExceptionHandler();
//TODO: when SequenceReportingEventHandler is defined
//            if (eventHandler instanceof SequenceReportingEventHandler)
//            {
//                ((SequenceReportingEventHandlavailableSequenceer<?>)eventHandler).setSequenceCallback(sequence);
//            }
        }

        ~BatchEventProcessor()
        {
            delete exceptionHandler;
        }


        hba::atomic::AtomicInt64* getSequence() {return &sequence;}

        void setExceptionHandler(ExceptionHandler *exceptionHandler)
        {
            if (exceptionHandler==nullptr) throw hba::NullPointerException();
            this->exceptionHandler = exceptionHandler;
        }


        void halt()
        {
            running.set(false);
            sequenceBarrier->alert();
        }


        void run()
        {
            if (!running.compareAndSet(false, true)) {
                throw hba::IllegalStateException("Thread is already running");
            }
            sequenceBarrier->clearAlert();

            notifyStart();

            T *event;
            int64_t nextSequence = sequence.get() + 1;
            while (true) {
                try {
                    int64_t availableSequence = sequenceBarrier->waitFor(nextSequence);
                    while (nextSequence <= availableSequence) {
                        event = ringBuffer->get(nextSequence);
                        eventHandler->onEvent(*event, nextSequence, nextSequence == availableSequence);
                        nextSequence++;
                    }

                    sequence.set(nextSequence - 1);
                }
                catch (AlertException ex) {
                   if (!running.get()) break;
                }
                catch (std::exception ex) {
                    exceptionHandler->handleEventException(ex, nextSequence, &event);
                    sequence.set(nextSequence);
                    nextSequence++;
                }
            }

            notifyShutdown();

            running.set(false);
        }

        RingBuffer<T>* getRingBuffer() {return ringBuffer;}


        std::size_t hashCode() const
        {
            return std::hash<const void *>()(this);
        }

    private:
        void notifyStart()
        {
            try {
                eventHandler->onStart();
            } catch (std::exception ex) {
                exceptionHandler->handleOnStartException(ex);
            }
        }

        void notifyShutdown()
        {
            try {
                eventHandler->onShutdown();
            } catch (std::exception ex) {
                exceptionHandler->handleOnStartException(ex);
            }
        }

    };

}

#endif // BATCHEVENTPROCESSOR_H

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
 *
 * This code is a porting, from Java to C++, of the Disruptor pattern
 * developed by LMAX. The original Java code can be found at:
 *
 * http://code.google.com/p/disruptor/
 */
#ifndef DISRUPTOR_H
#define DISRUPTOR_H

#include <stdarg.h>
#include "baseDisruptorClass.h"
#include "garbageList.h"
#include "ringBuffer.h"
#include "threadExecutor.h"
#include "eventProcessorRepository.h"
#include "atomicBool.h"
#include "eventPublisher.h"
#include "exceptionHandler.h"
#include "eventInitializer.h"
#include "claimStrategy.h"
#include "waitStrategy.h"
#include "eventHandlerGroup.h"
#include "batchEventProcessor.h"

namespace disruptor {

    /**
     * @brief
     * A DSL-style API for setting up the disruptor pattern around a ring buffer.
     *
     * A simple example of setting up the disruptor with two event handlers that must process events in order:
     *
     * <pre><code>
     * Disruptor<MyEvent> *disruptor = new Disruptor<MyEvent>(MyEvent.INITIALIZER, 32);
     * EventHandler<MyEvent> *handler1 = new EventHandler<MyEvent>() { ... };
     * EventHandler<MyEvent> *handler2 = new EventHandler<MyEvent>() { ... };
     * EventHandler<MyEvent> *handler3 = new EventHandler<MyEvent>() { ... };
     *
     *
     * EventHandler<TestEvent> **testEventHandlers1 = (EventHandler<TestEvent> **)new TestEventHandler*[2];
     * EventHandler<TestEvent> **testEventHandlers2 = (EventHandler<TestEvent> **)new TestEventHandler*[1];
     * testEventHandlers1[0] = handler1;
     * testEventHandlers1[1] = handler2;
     * testEventHandlers2[0] = handler3;
     *
     * disruptor->handleEventsWith(testEventHandlers1, 2)->then(testEventHandlers2, 1);
     *
     * RingBuffer *ringBuffer = disruptor.start();
     *
     * int64_t sequence = ringBuffer->next();
     * MyEvent *event = ringBuffer->get(sequence);
     * ... do something with event
     * ringBuffer->publish(sequence);
     *</code></pre>
     *
     * @param <T> the type of event used.
     */
    template <class T>
    class Disruptor : public BaseDisruptorClass
    {
    private:
        RingBuffer<T> *ringBuffer;
        EventProcessorRepository<T> eventProcessorRepository;
        hba::atomic::AtomicBool started;
        EventPublisher<T> *eventPublisher;
        ExceptionHandler *exceptionHandler;
        ThreadExecutor **executors;

        GarbageList garbageList;

     public:
        /**
         * @brief Disruptor
         * Create a new Disruptor.
         *
         * @param eventInitializer to initialize entries in the RingBuffer after creation.
         * @param ringBufferSize   the size of the ring buffer.
         */
        Disruptor(EventInitializer<T> &eventInitializer, int ringBufferSize)
        {
            ringBuffer = new RingBuffer<T>(eventInitializer, ringBufferSize);
            garbageList.add(ringBuffer);
            eventPublisher = new EventPublisher<T>(ringBuffer);
            garbageList.add(eventPublisher);
            executors = nullptr;
            exceptionHandler = nullptr;
        }

        /**
         * @brief Disruptor
         * Create a new Disruptor.
         *
         * @param eventInitializer to initialize entries in the RingBuffer after creation.
         * @param claimStrategy    the claim strategy to use for the ring buffer.
         * @param waitStrategy     the wait strategy to use for the ring buffer.
         */
        Disruptor(EventInitializer<T> &eventInitializer,
                  ClaimStrategy *claimStrategy,
                  WaitStrategy *waitStrategy) : started(false)
        {
            ringBuffer = new RingBuffer<T>(eventInitializer, claimStrategy, waitStrategy);
            garbageList.add(ringBuffer);
            eventPublisher = new EventPublisher<T>(ringBuffer);
            garbageList.add(eventPublisher);
            executors = nullptr;
            exceptionHandler = nullptr;
        }

        ~Disruptor()
        {
            if (executors!=nullptr) delete [] executors;
            delete eventPublisher;
         }

        /**
         * @brief handleExceptionsWith
         * Specify an exception handler to be used for any future event handlers.
         * Note that only event handlers set up after calling this method will use the exception handler.
         *
         * @param exceptionHandler the exception handler to use for any future EventProcessor.
         */
        void handleExceptionsWith(const ExceptionHandler *exceptionHandler)
        {
            this->exceptionHandler = exceptionHandler;
        }

        /**
         * @brief after
         * Create a group of event handlers to be used as a dependency.
         * For example if the handler A must process events before handler B:
         * <pre><code>
         * dw.after(A, 1)->handleEventsWith(B, 1);
         * </code></pre>
         *
         * @param numberOfHandlers number of event handlers
         * @param one or more event handlers, previously set up withhandleEventsWith(EventHandler, ... )},
         *                 that will form the barrier for subsequent handlers or processors.
         * @return an EventHandlerGroup that can be used to setup a dependency barrier over the specified event handlers.
         */
        EventHandlerGroup<T>* after(const int numberOfHandlers, EventHandler<T> *handler, ...)
        {
            EventProcessor **selectedEventProcessors = new EventProcessor*[numberOfHandlers];
            va_list args;
            va_start(args, handler);
            EventHandler<T> *p = handler;
            int i = 0;
            do {
                selectedEventProcessors[i] = eventProcessorRepository.getEventProcessorFor(p);

                p = va_arg(args, EventHandler<T> *);
                i++;
            } while (i<numberOfHandlers);
            va_end(args);

            EventHandlerGroup<T> *group = new EventHandlerGroup<T>(this, &eventProcessorRepository, selectedEventProcessors, numberOfHandlers);
            garbageList.add(group);
            return group;
        }

        /**
         * @brief after
         * Create a group of event processors to be used as a dependency.
         *
         * @param numberOfProcessors number of evet procesors.
         * @param one or more event processors, previously set up with handleEventsWith(EventProcessor...),
         *                   that will form the barrier for subsequent handlers or processors.
         * @return an EventHandlerGroup that can be used to setup a SequenceBarrier over hte specified event processors.
         */
        EventHandlerGroup<T>* after(const int numberOfProcessors, EventProcessor *processor, ...)
        {
            EventProcessor **selectedEventProcessors = new EventProcessor*[numberOfProcessors];
            va_list args;
            va_start(args, processor);
            EventHandler<T> *p = processor;
            int i = 0;
            do {
                eventProcessorRepository.add(p);
                selectedEventProcessors[i] = p;

                p = va_arg(args, EventHandler<T> *);
                i++;
            } while (i<numberOfProcessors);
            va_end(args);

            EventHandlerGroup<T> *group = new EventHandlerGroup<T>(this, &eventProcessorRepository, selectedEventProcessors, numberOfProcessors);
            garbageList.add(group);
            return group;
        }

        /**
         * @brief publishEvent
         * Publish an event to the ring buffer.
         *
         * @param eventTranslator the translator that will load data into the event.
         */
        void publishEvent(const EventTranslator<T> &eventTranslator)
        {
            eventPublisher->publishEvent(eventTranslator);
        }

        /**
         * @brief start
         * Starts the event processors and returns the fully configured ring buffer.
         * The ring buffer is set up to prevent overwriting any entry that is yet to
         * be processed by the slowest event processor.
         * This method must only be called once after all event processors have been added.
         *
         * @return pointer to the configured ring buffer.
         */
        RingBuffer<T>* start()
        {
            EventProcessorArray *gatingProcessors = eventProcessorRepository.getLastEventProcessorsInChain();
            ringBuffer->setGatingSequences(*(Util::getSequencesFor(*gatingProcessors)));

            if (!started.compareAndSet(false, true)) throw hba::IllegalStateException("Disruptor.start() must only be called once.");

            executors = new ThreadExecutor*[eventProcessorRepository.size()+1];
            int inx = 0;
            EventProcessorInfo<T> *eventProcessorInfo = eventProcessorRepository.getFirst();
            while (eventProcessorInfo != nullptr) {
                executors[inx] = new ThreadExecutor(eventProcessorInfo->getEventProcessor());
                executors[inx]->start();
                eventProcessorInfo = eventProcessorRepository.getNext();
                inx++;
            }
            executors[inx] = nullptr;

            return ringBuffer;
        }

        /**
         * @brief halt
         * Calls EventProcessor.halt() on all of the event processors created via this disruptor.
         **/
        void halt()
        {
            for (int i=0; executors[i]!=nullptr; i++) {
                executors[i]->stop();
            }
            delete [] executors;
            executors = nullptr;
        }

        /**
         * @brief shutdown
         * Waits until all events currently in the disruptor have been processed by all event processors
         * and then halts the processors.  It is critical that publishing to the ring buffer has stopped
         * before calling this method, otherwise it may never return.
         *
         * This method will not shutdown the executor, nor will it await the final termination of the
         * processor threads.
         **/
        void shutdown()
        {
            while (hasBacklog())
            {
                // Busy spin
            }
            halt();
        }



        /**
         * @brief getRingBuffer
         * The the RingBuffer}used by this Disruptor. This is useful for creating custom
         * event processors if the behaviour of BatchEventProcessor is not suitable.
         *
         * @return the ring buffer used by this Disruptor.
         **/
        RingBuffer<T>* getRingBuffer() {return ringBuffer;}

        /**
         * @brief getBarrierFor
         * Get the SequenceBarrier used by a specific handler. Note that the SequenceBarrier
         * may be shared by multiple event handlers.
         *
         * @param handler the handler to get the barrier for.
         * @return a pointer to the SequenceBarrier used by handler.
         **/
        SequenceBarrier* getBarrierFor(const EventHandler<T> &handler) {return eventProcessorRepository.getBarrierFor(handler);}


        /**
         * @brief handleEventsWith
         * Set up event handlers to handle events from the ring buffer. These handlers will process events
         * as soon as they become available, in parallel.
         *
         * This method can be used as the start of a chain. For example if the handler A must
         * process events before handler B:
         * <pre><code>
         * dw.handleEventsWith(A, 1)->then(B, 1);
         * </code></pre>
         *
         * @param numberOfHandlers number of event handlers
         * @param handler one or more event handlers
         * @return a EventHandlerGroup that can be used to chain dependencies.
         **/
        EventHandlerGroup<T>* handleEventsWith(const int numberOfHandlers, EventHandler<T> *handler, ...)
        {
            va_list args;
            va_start(args, handler);
            EventHandler<T> *p = handler;
            EventHandlerGroup<T>* group =  createEventProcessors(*(new EventProcessorArray(0)), numberOfHandlers, p, args);
            va_end(args);
            return group;
        }

        /**
         * @brief handleEventsWith
         * Set up custom event processors to handle events from the ring buffer. The Disruptor will
         * automatically start this processors when start() is called.
         *
         * @param numberOfProcessors number of evet Procesors.
         * @param processor one or more event processor the will precess events.
         * @return a EventHandlerGroup that can be used to chain dependencies.
         **/
        EventHandlerGroup<T>* handleEventsWith(const int numberOfProcessors, EventProcessor *processor, ...)
        {
            EventProcessor **createdEventProcessors[numberOfProcessors];
            va_list args;
            va_start(args, processor);
            createdEventProcessors[0] = processor;
            for (int i = 1; i < numberOfProcessors; i++) {
                createdEventProcessors[i] = va_arg(args, EventProcessor *);
            }
            va_end(args);
            EventHandlerGroup<T> *retVal = new EventHandlerGroup<T>(this, &eventProcessorRepository, createdEventProcessors, numberOfProcessors);
            garbageList.add(retVal);
            return retVal;
        }


        /**
         * @brief createEventProcessors
         * @param barrierEventProcessors
         * @param numberOfHandlers
         * @param handler
         * @param args
         * @return
         */
        EventHandlerGroup<T> *createEventProcessors(EventProcessorArray &barrierEventProcessors,
                                                    const int numberOfHandlers,
                                                    EventHandler<T> *handler,
                                                    va_list args)
        {
            if (started.get()) throw hba::IllegalStateException("All event handlers must be added before calling starts.");

            EventProcessorArray *createdEventProcessors = new EventProcessorArray(numberOfHandlers);
            garbageList.add((BaseDisruptorClass**)createdEventProcessors);
            SequenceBarrier *barrier = ringBuffer->newBarrier(*(Util::getSequencesFor(barrierEventProcessors)));
            garbageList.add(barrier);

            //va_list args;
            //va_start(args, handler);
            EventHandler<T> *p = handler;
            int i = 0;
            do {
                BatchEventProcessor<T> *batchEventProcessor = new BatchEventProcessor<T>(ringBuffer, barrier, p);
                garbageList.add(batchEventProcessor);

                if (exceptionHandler != nullptr) batchEventProcessor->setExceptionHandler(exceptionHandler);
                eventProcessorRepository.add((EventProcessor &)*batchEventProcessor, *p, *barrier);
                createdEventProcessors->set(batchEventProcessor, i);

                p = va_arg(args, EventHandler<T> *);
                i++;
            } while (i<numberOfHandlers);
            va_end(args);

            if (numberOfHandlers > 0) eventProcessorRepository.unMarkEventProcessorsAsEndOfChain(barrierEventProcessors);

            EventHandlerGroup<T> *retVal = new EventHandlerGroup<T>(this, &eventProcessorRepository, *createdEventProcessors);
            garbageList.add(retVal);
            return retVal;
        }


    private:
        //TODO: public ExceptionHandlerSetting<?> handleExceptionsFor(final EventHandler<T> eventHandler)

        bool hasBacklog()
        {
            int64_t cursor = ringBuffer->getCursor();
            EventProcessor** consumers = eventProcessorRepository.getLastEventProcessorsInChain();
            int inx = 0;
            while (consumers[inx] != nullptr) {
                if (cursor != consumers[inx]->getSequence()->get()) return true;
                inx++;
            }
            return false;
        }

    };
}

#endif // DISRUPTOR_H

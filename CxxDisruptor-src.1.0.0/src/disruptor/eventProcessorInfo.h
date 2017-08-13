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
#ifndef EVENTPROCESSORINFO_H
#define EVENTPROCESSORINFO_H

#include "baseDisruptorClass.h"
#include "eventProcessor.h"
#include "eventHandler.h"
#include "sequenceBarrier.h"

namespace disruptor {

    template <class T>
    class EventProcessorInfo : public BaseDisruptorClass
    {
    private:
        EventProcessor *eventprocessor;
        EventHandler<T> *handler;
        SequenceBarrier *barrier;
        bool endOfChain;

    public:
        EventProcessorInfo(EventProcessor &eventprocessor)
        {
            this->eventprocessor = &eventprocessor;
            this->handler = nullptr;
            this->barrier = nullptr;
            endOfChain = true;
        }

        EventProcessorInfo(EventProcessor &eventprocessor, EventHandler<T> &handler, SequenceBarrier &barrier)
        {
            this->eventprocessor = &eventprocessor;
            this->handler = &handler;
            this->barrier = &barrier;
            endOfChain = true;
        }

        EventProcessor* getEventProcessor() {return eventprocessor;}
        EventHandler<T>* getHandler() {return handler;}
        SequenceBarrier* getBarrier() {return barrier;}
        bool isEndOfChain() {return endOfChain;}
        void markAsUsedInBarrier() {endOfChain = false;}
        size_t hashCode() const
        {
            return (size_t)(&eventprocessor + &handler + &barrier);
        }
    };

}

namespace std {
    template <class T>
    class hash<disruptor::EventProcessorInfo<T>> {
    public :
        size_t operator()(const disruptor::EventProcessorInfo<T> &eventProcessorInfo ) const {
            return eventProcessorInfo.hashCode();
        }
    };

}

#endif // EVENTPROCESSORINFO_H

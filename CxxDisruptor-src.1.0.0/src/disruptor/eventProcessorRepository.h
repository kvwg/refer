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
#ifndef EVENTPROCESSORREPOSITORY_H
#define EVENTPROCESSORREPOSITORY_H

#include <vector>

#include "baseDisruptorClass.h"
#include "garbageList.h"
#include "identityHashMap.h"
#include "eventProcessorInfo.h"
#include "eventProcessorArray.h"
#include "eventHandler.h"
#include "sequenceBarrier.h"
#include "illegalArgumentException.h"


namespace disruptor {

    template <class T>
    class EventProcessorRepository : public BaseDisruptorClass
    {
    private:
        hba::IdentityHashMap<EventHandler<T>, EventProcessorInfo<T>> eventProcessorInfoByHandler;
        hba::IdentityHashMap<EventProcessor, EventProcessorInfo<T>> eventProcessorInfoByEventProcessor;
        GarbageList garbage;

    public:
        EventProcessorRepository() : eventProcessorInfoByHandler(0x100), eventProcessorInfoByEventProcessor(0x100)
//        EventProcessorRepository() : eventProcessorInfoByHandler(8), eventProcessorInfoByEventProcessor(8)
        {
        }

        void add(EventProcessor &eventprocessor, EventHandler<T> &handler, SequenceBarrier &barrier)
        {
            EventProcessorInfo<T> *eventProcessorInfo = new EventProcessorInfo<T>(eventprocessor, handler, barrier);
            garbage.add(eventProcessorInfo);
            eventProcessorInfoByHandler.put(handler, *eventProcessorInfo);
            eventProcessorInfoByEventProcessor.put(eventprocessor, *eventProcessorInfo);
        }

        void add(EventProcessor &processor)
        {
            EventProcessorInfo<T> *eventProcessorInfo = new EventProcessorInfo<T>(processor);
            garbage.add(eventProcessorInfo);
            eventProcessorInfoByEventProcessor.put(processor, *eventProcessorInfo);
        }

        EventProcessorArray* getLastEventProcessorsInChain()
        {
            EventProcessor* lastEventProcessorsArr[eventProcessorInfoByEventProcessor.getPopulation()];
            int inx = 0;
            EventProcessorInfo<T> *eventProcessorInfo = eventProcessorInfoByEventProcessor.iteratorFirst();
            while (eventProcessorInfo!=nullptr) {
                if (eventProcessorInfo->isEndOfChain()) {
                    lastEventProcessorsArr[inx++] = eventProcessorInfo->getEventProcessor();
                }
                eventProcessorInfo = eventProcessorInfoByEventProcessor.iteratorNext();
            }

            EventProcessorArray * retVal = new EventProcessorArray(inx, lastEventProcessorsArr);
            garbage.add(retVal);
            return retVal;
        }

        EventProcessor* getEventProcessorFor(const EventHandler<T> &handler)
        {
            EventProcessorInfo<T> *eventprocessorInfo = eventProcessorInfoByHandler.get(handler);
            if (eventprocessorInfo == nullptr)
            {
                throw hba::IllegalArgumentException("The passed event handler is not processing events.");
            }

            return eventprocessorInfo->getEventProcessor();

        }

        // depricated
        void unMarkEventProcessorsAsEndOfChain(EventProcessor *barrierEventProcessors[], const int barrierEventProcessorsLength)
        {
            for (int i=0; i<barrierEventProcessorsLength; i++) {
                EventProcessorInfo<T> *info = eventProcessorInfoByEventProcessor.get(*barrierEventProcessors[i]);
                if (info!=nullptr) info->markAsUsedInBarrier();
            }
        }

        void unMarkEventProcessorsAsEndOfChain(EventProcessorArray &barrierEventProcessors)
        {
            for (int i=0; i<barrierEventProcessors.size(); i++) {
                EventProcessorInfo<T> *info = eventProcessorInfoByEventProcessor.get(barrierEventProcessors[i]);
                if (info!=nullptr) info->markAsUsedInBarrier();
            }
        }

        SequenceBarrier* getBarrierFor(const EventHandler<T> &handler)
        {
            EventProcessorInfo<T> *eventProcessorInfo = eventProcessorInfoByHandler.get(handler);
            return eventProcessorInfo != nullptr ? eventProcessorInfo->getBarrier() : nullptr;
        }

        int size()
        {
            return eventProcessorInfoByEventProcessor.getPopulation();
        }

        EventProcessorInfo<T>* getFirst()
        {
            return eventProcessorInfoByEventProcessor.iteratorFirst();
        }

        EventProcessorInfo<T>* getNext()
        {
            return eventProcessorInfoByEventProcessor.iteratorNext();
        }
    };

}

#endif // EVENTPROCESSORREPOSITORY_H

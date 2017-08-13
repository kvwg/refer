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
#ifndef EVENTPROCESSOR_H
#define EVENTPROCESSOR_H

#include <functional>
#include "baseDisruptorClass.h"
#include "atomicInt64.h"

namespace disruptor {

    /**
     * @brief Interface
     * EventProcessors waitFor events to become available for consumption from the RingBuffer
     *
     * An EventProcessor will be associated with a Thread for execution.
     */
    class EventProcessor : public BaseDisruptorClass
    {
    public:
        /**
         * @brief getSequence
         * Get a reference to the Sequence being used by this EventProcessor.
         *
         * @return reference to the Sequence for this EventProcessor
         */
        virtual hba::atomic::AtomicInt64* getSequence() = 0;

        /**
         * Signal that this EventProcessor should stop when it has finished consuming at the next clean break.
         * It will call SequenceBarrier.alert() to notify the thread to check status.
         */
        virtual void halt() = 0;

        /**
         * @brief run
         * The Run method is called by the thread there inwoke the object there implementing
         * the EventProcessor interface. This method should contain all the code wor the
         * work the implementing object has to do.
         */
        virtual void run() = 0;

        virtual std::size_t hashCode() const = 0;
    };
}

namespace std {
    template <>
    class hash<disruptor::EventProcessor> {
    public :
        size_t operator()(const disruptor::EventProcessor &eventProcessor ) const {
            return eventProcessor.hashCode();
        }
    };
}


#endif // EVENTPROCESSOR_H

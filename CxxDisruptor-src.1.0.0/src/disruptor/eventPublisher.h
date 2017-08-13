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
#ifndef EVENTPUBLISHER_H
#define EVENTPUBLISHER_H

#include "baseDisruptorClass.h"
#include "ringBuffer.h"
#include "eventTranslator.h"
#include "insufficientCapacityException.h"

/**
 * Utility class for simplifying publication to the ring buffer.
 */
namespace disruptor {

    /**
     * @brief
     * Utility class for simplifying publication to the ring buffer.
     */
    template <class T>
    class EventPublisher : public BaseDisruptorClass
    {
    private:
        RingBuffer<T> *ringBuffer;

    public:
        /**
         * @brief EventPublisher
         * Construct from the ring buffer to be published to.
         * @param ringBuffer into which events will be published.
         */
        EventPublisher(RingBuffer<T> *ringBuffer)
        {
            this->ringBuffer = ringBuffer;
        }

        /**
         * @brief publishEvent
         * Publishes an event to the ring buffer.  It handles
         * claiming the next sequence, getting the current (uninitialized)
         * event from the ring buffer and publishing the claimed sequence
         * after translation.
         *
         * @param translator The user specified translation for the event
         */
        void publishEvent(const EventTranslator<T> &translator)
        {
            int64_t sequence = ringBuffer->next();
            translateAndPublish(translator, sequence);
        }

        /**
         * @brief tryPublishEvent
         * Attempts to publish an event to the ring buffer.  It handles
         * claiming the next sequence, getting the current (uninitialized)
         * event from the ring buffer and publishing the claimed sequence
         * after translation.  Will return false if specified capacity
         * was not available.
         *
         * @param translator The user specified translation for the event
         * @param capacity The capacity that should be available before publishing
         * @return true if the value was published, false if there was insufficient
         * capacity.
         */
        bool tryPublishEvent(EventTranslator<T> &translator, int capacity)
        {
            try {
                int64_t sequence = ringBuffer->tryNext(capacity);
                translateAndPublish(translator, sequence);
                return true;
            } catch (InsufficientCapacityException ex) {
                return false;
            }
        }

    private:
        void translateAndPublish(const EventTranslator<T> &translator, const int64_t sequence)
        {
            translator.translateTo(ringBuffer->get(sequence), sequence);
            ringBuffer->publish(sequence);
        }

    };

}

#endif // EVENTPUBLISHER_H

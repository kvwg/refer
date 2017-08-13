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
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "sequencer.h"
#include "eventInitializer.h"
//#include "singleThreadedClaimStrategy.h"
//#include "yieldingWaitStrategy.h"
#include "multiThreadedClaimStrategy.h"
#include "blockingWaitStrategy.h"

namespace disruptor {

    /**
     * @brief
     * Ring based store of reusable entries containing the data representing an event being exchanged
     * between event publisher and EventProcessors.
     *
     * @param <T> implementation storing the data for sharing during exchange or parallel coordination of an event.
     */
    template <class T>
    class RingBuffer : public Sequencer
    {
    private:
        int indexMask;
        T *entries;
        int entriesSize = 0;

    public:
        /**
         * @brief RingBuffer
         * Construct a RingBuffer with the full option set.
         *
         * @param eventInitializer to initialize entries in the RingBuffer after creation.
         * @param claimStrategy threading strategy for publisher claiming entries in the ring.
         * @param waitStrategy waiting strategy employed by processorsToTrack waiting on entries becoming available.
         *
         * @throws IllegalArgumentException if bufferSize is not a power of 2
         */
        RingBuffer(EventInitializer<T> &eventInitializer,
                   ClaimStrategy *claimStrategy,
                   WaitStrategy *waitStrategy) : Sequencer(claimStrategy, waitStrategy)
        {
            if (Util::bitCount(claimStrategy->getBufferSize()) != 1) throw hba::IllegalArgumentException("bufferSize must be a power of 2");
            entriesSize = claimStrategy->getBufferSize();
            indexMask = entriesSize - 1;

            entries = new T[entriesSize];
            for (int i=0; i<entriesSize; i++) {
                eventInitializer.init(entries[i]);
            }
        }

        /**
         * @brief RingBuffer
         * Construct a RingBuffer with default strategies of:
         * MultiThreadedClaimStrategy and BlockingWaitStrategy
         *
         * @param eventInitializer to initialize entries in the RingBuffer after creation.
         * @param bufferSize of the RingBuffer that will be rounded up to the next power of 2
         *
         * @throws IllegalArgumentException if bufferSize is not a power of 2
         */
        RingBuffer(EventInitializer<T> &eventInitializer, int bufferSize) :
            RingBuffer(eventInitializer,
                       new MultiThreadedClaimStrategy(bufferSize),
                       new BlockingWaitStrategy())
        {}

        ~RingBuffer()
        {
            delete [] entries;
        }

        /**
         * @brief get
         * Get the event for a given sequence in the RingBuffer.
         *
         * @param sequence for the event
         * @return pointer to the event for the sequence
         */
        T* get(const int64_t sequence)
        {
             return &entries[(int)sequence & indexMask];
        }
    };

}

#endif // RINGBUFFER_H

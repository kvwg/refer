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
#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "sequenceArray.h"
#include "baseDisruptorClass.h"
#include "claimStrategy.h"
#include "waitStrategy.h"
#include "processingSequenceBarrier.h"
#include "garbageList.h"
#include "util.h"
#include "nullPointerException.h"
#include "illegalArgumentException.h"

namespace disruptor {
    /**
     * @brief
     * Coordinator for claiming sequences for access to a data structure while tracking dependent Sequences
     */
    class Sequencer : public BaseDisruptorClass
    {
    private:
        hba::atomic::AtomicInt64 cursor;
        SequenceArray *gatingSequences;

        ClaimStrategy *claimStrategy;
        WaitStrategy *waitStrategy;

        GarbageList garbage;

    public:
        /**
         * @brief Sequencer
         * Construct a Sequencer with the selected strategies.
         *
         * @param claimStrategy for those claiming sequences.
         * @param waitStrategy for those waiting on sequences.
         */
        Sequencer(ClaimStrategy *claimStrategy, WaitStrategy *waitStrategy);

        ~Sequencer();

        /**
         * @brief setGatingSequences
         * Set the sequences that will gate publishers to prevent the buffer wrapping.
         *
         * This method must be called prior to claiming sequences otherwise
         * a NullPointerException will be thrown.
         *
         * @param sequences to be to be gated on.
         */
        void setGatingSequences(SequenceArray &sequences) {
            gatingSequences = &sequences;
        }

        /**
         * @brief newBarrier
         * Create a SequenceBarrier that gates on the the cursor and a list of Sequences
         *
         * @param sequencesToTrack this barrier will track
         * @return pointer to the barrier gated as required
         */
        SequenceBarrier* newBarrier(SequenceArray &sequencesToTrack) {
            ProcessingSequenceBarrier *retVal = new ProcessingSequenceBarrier(waitStrategy, &cursor, sequencesToTrack);
            garbage.add(retVal);
            return retVal;
        }

        ProcessingSequenceBarrier newBarrierTest(SequenceArray &sequencesToTrack) {
            ProcessingSequenceBarrier retVal(waitStrategy, &cursor, sequencesToTrack);
            return retVal;
        }

        //TODO: BatchDescriptor newBatchDescriptor(const int size);

        /**
         * @brief getBufferSize
         * The capacity of the data structure to hold entries.
         *
         * @return the size of the RingBuffer.
         */
        int getBufferSize() {return claimStrategy->getBufferSize();}

        /**
         * @brief getCursor
         * Get the value of the cursor indicating the published sequence.
         *
         * @return value of the cursor for events that have been published.
         */
        int64_t getCursor() {return cursor.get();}

        /**
         * Has the buffer got capacity to allocate another sequence.  This is a concurrent
         * method so the response should only be taken as an indication of available capacity.
         *
         * @param availableCapacity in the buffer
         * @return true if the buffer has the capacity to allocate the next sequence otherwise false.
         */
        bool hasAvailableCapacity(const int availableCapacity) {
            return claimStrategy->hasAvailableCapacity(availableCapacity, *gatingSequences);
        }

        /**
         * @brief next
         * Claim the next event in sequence for publishing.
         *
         * @return the claimed sequence value
         */
        int64_t next();

        /**
         * @brief tryNext
         * Attempt to claim the next event in sequence for publishing.  Will return the
         * number of the slot if there is at least requiredCapacity slots
         * available.
         *
         * @param requiredCapacity as slots in the data structure
         * @return the claimed sequence value
         * @throws InsufficientCapacityException when the requiredCapacity is not available
         */
        int64_t tryNext(int requiredCapacity);

        //TODO: BatchDescriptor next(const BatchDescriptor batchDescriptor);

        /**
         * @brief claim
         * Claim a specific sequence when only one publisher is involved.
         *
         * @param sequence to be claimed.
         * @return sequence just claimed.
         */
        int64_t claim(const int64_t sequence);

        /**
         * Publish an event and make it visible to {@link EventProcessor}s
         *
         * @param sequence to be published
         */
        void publish(const int64_t sequence);

        //TODO: void publish(const BatchDescriptor batchDescriptor);

        /**
         * @brief forcePublish
         * Force the publication of a cursor sequence.
         *
         * Only use this method when forcing a sequence and you are sure only one publisher exists.
         * This will cause the cursor to advance to this sequence.
         *
         * @param sequence which is to be forced for publication.
         */
        void forcePublish(const int64_t sequence);

        int64_t remainingCapacity();

    private:
        void publish(const int64_t sequence, const int batchSize);
    };

}

#endif // SEQUENCER_H

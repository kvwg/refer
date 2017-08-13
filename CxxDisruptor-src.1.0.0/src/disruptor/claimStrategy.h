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
#ifndef CLAIMSTRATEGY_H
#define CLAIMSTRATEGY_H

#include "sequenceArray.h"
#include "baseDisruptorClass.h"
#include "atomicInt64.h"

using namespace hba::atomic;

namespace disruptor {

    /**
     * @brief Interface
     * Strategy contract for claiming the sequence of events in the Sequencer by event publishers.
     */
    class ClaimStrategy : public BaseDisruptorClass
    {
    public:
        /**
         * @brief getBufferSize
         * Get the size of the data structure used to buffer events.
         *
         * @return size of the underlying buffer.
         */
        virtual int getBufferSize() = 0;

        /**
         * @brief getSequence
         * Get the current claimed sequence.
         *
         * @return the current claimed sequence.
         */
        virtual int64_t getSequence() = 0;

        /**
         * @brief hasAvailableCapacity
         * Is there available capacity in the buffer for the requested sequence.
         *AtomicInt64
         * @param availableCapacity remaining in the buffer.
         * @param dependentSequences to be checked for range.
         * @param dependentSequencesLength number of elements in dependentSequences.
         * @return true if the buffer has capacity for the requested sequence.
         */
        virtual bool hasAvailableCapacity(const int availableCapacity, SequenceArray &dependentSequences) = 0;

        /**
         * @brief incrementAndGet
         * Claim the next sequence in the Sequencer.
         * The caller should be held up until the claimed sequence is available by tracking the dependentSequences.
         *
         * @param dependentSequences to be checked for range.
         * @param dependentSequencesLength number of elements in dependentSequences.
         * @return the index to be used for the publishing.
         */
        virtual int64_t incrementAndGet(SequenceArray &dependentSequences) = 0;

        /**
         * @brief incrementAndGet
         * Increment sequence by a delta and get the result.
         * The caller should be held up until the claimed sequence batch is available by tracking the dependentSequences.
         *
         * @param delta to increment by.
         * @param dependentSequences to be checked for range.
         * @param dependentSequencesLength number of elements in dependentSequences.
         * @return the result after incrementing.
         */
        virtual int64_t incrementAndGet(const int delta, SequenceArray &dependentSequences) = 0;

        /**
         * @brief setSequence
         * Set the current sequence value for claiming an event in the {@link Sequencer}
         * The caller should be held up until the claimed sequence is available by tracking the dependentSequences.
         *
         * @param dependentSequences to be checked for range.
         * @param dependentSequencesLength number of elements in dependentSequences.
         * @param sequence to be set as the current value.
         */
        virtual void setSequence(const int64_t sequence, SequenceArray &dependentSequences) = 0;

        /**
         * @brief serialisePublishing
         * Serialise publishers in sequence and set cursor to latest available sequence.
         *
         * @param sequence sequence to be applied
         * @param cursor to serialise against.
         * @param batchSize of the sequence.
         */
        virtual void serialisePublishing(const int64_t sequence, AtomicInt64 &cursor, const int batchSize) = 0;

        /**
         * @brief checkAndIncrement
         * Atomically checks the available capacity of the ring buffer and claims the next sequence.  Will
         * throw InsufficientCapacityException if the capacity not available.
         *
         * @param availableCapacity the capacity that should be available before claiming the next slot
         * @param delta the number of slots to claim
         * @param gatingSequences the set of sequences to check to ensure capacity is available
         * @param gatingSequencesLength number of elements in gatingSequences.
         * @return the slot after incrementing
         * @throws InsufficientCapacityException thrown if capacity is not available
         */
        virtual int64_t checkAndIncrement(int availableCapacity, int delta, SequenceArray &gatingSequences) = 0;
    };

}

#endif // CLAIMSTRATEGY_H

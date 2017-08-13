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
#ifndef SINGLETHREADEDCLAIMSTRATEGY_H
#define SINGLETHREADEDCLAIMSTRATEGY_H

#include "claimStrategy.h"
#include "sequencer.h"
#include "paddedInt64.h"

namespace disruptor {

    /**
     * @brief Implements ClaimStrategy
     * Optimised strategy can be used when there is a single publisher thread claiming sequences.
     *
     * This strategy must NOT be used when multiple threads are used for publishing concurrently on the same Sequencer
     */
    class SingleThreadedClaimStrategy : public ClaimStrategy
    {
    private:
        int bufferSize;
        PaddedInt64 minGatingSequence;
        PaddedInt64 claimSequence;

        void waitForFreeSlotAt(const int64_t sequence, SequenceArray &dependentSequences);

    public:
        SingleThreadedClaimStrategy(const int bufferSize);

        int getBufferSize() {return bufferSize;}
        int64_t getSequence() {return claimSequence.get();}

        bool hasAvailableCapacity(const int availableCapacity, SequenceArray &dependentSequences);
        int64_t incrementAndGet(SequenceArray &dependentSequences);
        int64_t incrementAndGet(const int delta, SequenceArray &dependentSequences);
        void setSequence(const int64_t sequence, SequenceArray &dependentSequences);
        void serialisePublishing(const int64_t sequence, AtomicInt64 &cursor, const int batchSize) {cursor.set(sequence);}
        int64_t checkAndIncrement(int availableCapacity, int delta, SequenceArray &dependentSequences);
    };

}

#endif // SINGLETHREADEDCLAIMSTRATEGY_H

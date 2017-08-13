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
#ifndef ABSTRACTMULTITHREADEDCLAIMSTRATEGY_H
#define ABSTRACTMULTITHREADEDCLAIMSTRATEGY_H

#include <thread>
#include "claimStrategy.h"
#include "atomicInt64Array.h"
#include "identityHashMap.h"
#include "paddedInt64.h"
#include "garbageList.h"

namespace disruptor {

    /**
     * @brief Implements ClaimStrategy
     */
    class AbstractMultithreadedClaimStrategy : public ClaimStrategy
    {
    private:
        int bufferSize;
        hba::atomic::AtomicInt64 claimSequence;
        hba::IdentityHashMap<std::thread::id, PaddedInt64> *minGatingSequenceThreadLocal;

        GarbageList garbage;

    public:
        AbstractMultithreadedClaimStrategy(const int bufferSize);
        ~AbstractMultithreadedClaimStrategy();

        int getBufferSize() {return bufferSize;}
        int64_t getSequence() {return claimSequence.get();}

        bool hasAvailableCapacity(const int availableCapacity, SequenceArray &dependentSequences);
        int64_t incrementAndGet(SequenceArray &dependentSequences);
        int64_t incrementAndGet(const int delta, SequenceArray &dependentSequences);
        void setSequence(const int64_t sequence, SequenceArray &dependentSequences);
        int64_t checkAndIncrement(int availableCapacity, int delta, SequenceArray &gatingSequences);

        virtual void serialisePublishing(const int64_t sequence, AtomicInt64 &cursor, const int batchSize) = 0;

    private:
        void waitForFreeSlotAt(const int64_t sequence, SequenceArray &dependentSequences, PaddedInt64 *minGatingSequence);
        bool hasAvailableCapacity(int64_t sequence, const int availableCapacity, SequenceArray &dependentSequences);
        PaddedInt64 *getMinGatingSequenceThreadLocal();
    };

}

#endif // ABSTRACTMULTITHREADEDCLAIMSTRATEGY_H

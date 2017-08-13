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
#ifndef MULTITHREADEDCLAIMSTRATEGY_H
#define MULTITHREADEDCLAIMSTRATEGY_H

#include <thread>
#include "abstractMultithreadedClaimStrategy.h"
#include "claimStrategy.h"
#include "atomicInt64Array.h"
#include "identityHashMap.h"
#include "paddedInt64.h"
#include "garbageList.h"

namespace disruptor {

    /**
     * @brief Inherit AbstractMultithreadedClaimStrategy
     * Strategy to be used when there are multiple publisher threads claiming sequences.
     *
     * This strategy is reasonably forgiving when the multiple publisher threads are highly contended or working in an
     * environment where there is insufficient CPUs to handle multiple publisher threads.  It requires 2 CAS operations
     * for a single publisher, compared to the MultiThreadedLowContentionClaimStrategy strategy which needs only a single
     * CAS and a lazySet per publication.
     */
    class MultiThreadedClaimStrategy : public AbstractMultithreadedClaimStrategy
    {
    private:
        static const int RETRIES = 1000;

        hba::atomic::AtomicInt64Array *pendingPublication;
        int pendingMask;

    public:
        MultiThreadedClaimStrategy(const int bufferSize, const int pendingBufferSize);
        MultiThreadedClaimStrategy(const int bufferSize) : MultiThreadedClaimStrategy(bufferSize, 1024){}
        ~MultiThreadedClaimStrategy();

        void serialisePublishing(const int64_t sequence, AtomicInt64 &cursor, const int batchSize);

    private:
    };

}

#endif // MULTITHREADEDCLAIMSTRATEGY_H

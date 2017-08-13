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
#ifndef BLOCKINGWAITSTRATEGY_H
#define BLOCKINGWAITSTRATEGY_H

#include <mutex>
#include <condition_variable>
#include "waitStrategy.h"

namespace disruptor {

    /**
     * @brief Implements WaitStrategy
     * Blocking strategy that uses a lock and condition variable for EventProcessors waiting on a barrier.
     *
     * This strategy can be used when throughput and low-latency are not as important as CPU resource.
     */
    class BlockingWaitStrategy : public WaitStrategy
    {
    private:
        std::mutex lockMutex;
        std::condition_variable processorNotifyCondition;

    public:
        BlockingWaitStrategy();
        int64_t waitFor(const int64_t sequence, AtomicInt64 &cursor, SequenceArray &dependents, SequenceBarrier &barrier);
        void signalAllWhenBlocking();
    };

}

#endif // BLOCKINGWAITSTRATEGY_H

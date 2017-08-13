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
#ifndef YIELDINGWAITSTRATEGY_H
#define YIELDINGWAITSTRATEGY_H

#include "waitStrategy.h"

namespace disruptor {

    /**
     * @brief Implements WaitStrategy
     * Yielding strategy that uses a Thread.yield() for EventProcessors waiting on a barrier
     * after an initially spinning.
     *
     * This strategy is a good compromise between performance and CPU resource without incurring significant latency spikes.
     */
    class YieldingWaitStrategy : public WaitStrategy
    {
    private:
        const int SPIN_TRIES = 100;

        int applyWaitMethod(SequenceBarrier &barrier, int counter);

    public:
        YieldingWaitStrategy();

        int64_t waitFor(const int64_t sequence, AtomicInt64 &cursor, SequenceArray &dependents, SequenceBarrier &barrier);
        void signalAllWhenBlocking();
    };

}

#endif // YIELDINGWAITSTRATEGY_H

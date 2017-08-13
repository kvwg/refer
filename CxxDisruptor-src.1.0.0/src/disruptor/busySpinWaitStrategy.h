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
#ifndef BUSYSPINWAITSTRATEGY_H
#define BUSYSPINWAITSTRATEGY_H

#include "waitStrategy.h"

namespace disruptor {

    /**
     * @brief Implements WaitStrategy
     * Busy Spin strategy that uses a busy spin loop for EventProcessors waiting on a barrier.
     *
     * This strategy will use CPU resource to avoid syscalls which can introduce latency jitter. It is best
     * used when threads can be bound to specific CPU cores (see Util::setAffinity()).
     */
    class BusySpinWaitStrategy : public WaitStrategy
    {
    public:
        BusySpinWaitStrategy() {}

        int64_t waitFor(const int64_t sequence, AtomicInt64 &cursor, SequenceArray &dependents, SequenceBarrier &barrier);
        void signalAllWhenBlocking() {}

    };

}

#endif // BUSYSPINWAITSTRATEGY_H

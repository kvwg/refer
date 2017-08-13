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
#ifndef WAITSTRATEGY_H
#define WAITSTRATEGY_H

#include "sequenceArray.h"
#include "baseDisruptorClass.h"
#include "atomicInt64.h"
#include "sequenceBarrier.h"

using namespace hba::atomic;

namespace disruptor {


    /**
     * @brief Interface
     * Strategy employed for making EventProcessors wait on a cursor Sequence.
     */
    class WaitStrategy : public BaseDisruptorClass
    {
    public:
        /**
         * @brief waitFor
         * Wait for the given sequence to be available
         *
         * @param sequence to be waited on.
         * @param cursor on which to wait.
         * @param dependents further back the chain that must advance first
         * @param dependentsLength number of elements in dependents
         * @param barrier the processor is waiting on.
         * @return the sequence that is available which may be greater than the requested sequence.
         * @throws AlertException if the status of the Disruptor has changed.
         * @throws InterruptedException if the thread is interrupted.
         */
        virtual int64_t waitFor(const int64_t sequence, AtomicInt64 &cursor, SequenceArray &dependents, SequenceBarrier &barrier) = 0;

        /**
         * @brief signalAllWhenBlocking
         * Signal those EventProcessors waiting that the cursor has advanced.
         */
        virtual void signalAllWhenBlocking() = 0;
    };
}


#endif // WAITSTRATEGY_H

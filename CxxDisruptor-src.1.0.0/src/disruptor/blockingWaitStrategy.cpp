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
#include "blockingWaitStrategy.h"
#include "alertException.h"
#include "util.h"

using namespace disruptor;

BlockingWaitStrategy::BlockingWaitStrategy()
{
}

int64_t BlockingWaitStrategy::waitFor(const int64_t sequence, AtomicInt64 &cursor, SequenceArray &dependents, SequenceBarrier &barrier)
{
    int64_t availableSequence;
    if ((availableSequence = cursor.get()) < sequence) {
        //std::lock(lockMutex);
        try {
            while ((availableSequence = cursor.get()) < sequence) {
                barrier.checkAlert();
                {
                    std::unique_lock<std::mutex> lk(lockMutex);
                    processorNotifyCondition.wait(lk);
                }
            }
        } catch (AlertException ignore) {}
        //std::lock.unlock();
    }

    if (0 != dependents.size()) {
        while ((availableSequence = Util::getMinimumSequence(dependents)) < sequence)
        {
            barrier.checkAlert();
        }
    }

    return availableSequence;

}

void BlockingWaitStrategy::signalAllWhenBlocking()
{
    //std::lock(lockMutex);
    processorNotifyCondition.notify_all();
    //std::lock.unlock();
}


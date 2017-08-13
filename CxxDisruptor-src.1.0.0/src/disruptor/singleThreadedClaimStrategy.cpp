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
#include <thread>
#include "singleThreadedClaimStrategy.h"
#include "insufficientCapacityException.h"
#include "util.h"

using namespace disruptor;

SingleThreadedClaimStrategy::SingleThreadedClaimStrategy(const int bufferSize) : minGatingSequence(hba::atomic::AtomicInt64::INITIAL_CURSOR_VALUE), claimSequence(hba::atomic::AtomicInt64::INITIAL_CURSOR_VALUE)
{
    this->bufferSize = bufferSize;
}

bool SingleThreadedClaimStrategy::hasAvailableCapacity(const int availableCapacity, SequenceArray &dependentSequences)
{
    const int64_t wrapPoint = (claimSequence.get() + availableCapacity) - bufferSize;
    if (wrapPoint > minGatingSequence.get())
    {
        int64_t minSequence = Util::getMinimumSequence(dependentSequences);
        minGatingSequence.set(minSequence);

        if (wrapPoint > minSequence)
        {
            return false;
        }
    }

    return true;

}

int64_t SingleThreadedClaimStrategy::incrementAndGet(SequenceArray &dependentSequences)
{
    int64_t nextSequence = claimSequence.get() + 1L;
    claimSequence.set(nextSequence);
    waitForFreeSlotAt(nextSequence, dependentSequences);

    return nextSequence;
}

int64_t SingleThreadedClaimStrategy::incrementAndGet(const int delta, SequenceArray &dependentSequences)
{
    int64_t nextSequence = claimSequence.get() + delta;
    claimSequence.set(nextSequence);
    waitForFreeSlotAt(nextSequence, dependentSequences);

    return nextSequence;
}

void SingleThreadedClaimStrategy::setSequence(const int64_t sequence, SequenceArray &dependentSequences)
{
    claimSequence.set(sequence);
    waitForFreeSlotAt(sequence, dependentSequences);
}

int64_t SingleThreadedClaimStrategy::checkAndIncrement(int availableCapacity, int delta, SequenceArray &dependentSequences)
{
    if (!hasAvailableCapacity(availableCapacity, dependentSequences))
    {
        throw InsufficientCapacityException();
    }

    return incrementAndGet(delta, dependentSequences);
}





void SingleThreadedClaimStrategy::waitForFreeSlotAt(const int64_t sequence, SequenceArray &dependentSequences)
{
    const int64_t wrapPoint = sequence - bufferSize;
    if (wrapPoint > minGatingSequence.get())
    {
        int64_t minSequence;
        while (wrapPoint > (minSequence = Util::getMinimumSequence(dependentSequences)))
        {
            //std::this_thread::sleep_until(1);
            std::this_thread::yield();
        }

        minGatingSequence.set(minSequence);
    }
}

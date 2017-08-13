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
#include "abstractMultithreadedClaimStrategy.h"
#include "util.h"
#include "insufficientCapacityException.h"

using namespace disruptor;

AbstractMultithreadedClaimStrategy::AbstractMultithreadedClaimStrategy(const int bufferSize) : claimSequence(hba::atomic::AtomicInt64::INITIAL_CURSOR_VALUE)
{
    this->bufferSize = bufferSize;

    minGatingSequenceThreadLocal = new hba::IdentityHashMap<std::thread::id, PaddedInt64>(1024);
}

AbstractMultithreadedClaimStrategy::~AbstractMultithreadedClaimStrategy()
{
    delete minGatingSequenceThreadLocal;
}


bool AbstractMultithreadedClaimStrategy::hasAvailableCapacity(const int availableCapacity, SequenceArray &dependentSequences)
{
    return hasAvailableCapacity(claimSequence.get(), availableCapacity, dependentSequences);
}

int64_t AbstractMultithreadedClaimStrategy::incrementAndGet(SequenceArray &dependentSequences)
{
    const int64_t nextSequence = claimSequence.addAndGet(1);
    waitForFreeSlotAt(nextSequence, dependentSequences, getMinGatingSequenceThreadLocal());

    return nextSequence;
}

int64_t AbstractMultithreadedClaimStrategy::incrementAndGet(const int delta, SequenceArray &dependentSequences)
{
    int64_t nextSequence = claimSequence.addAndGet(1);
    waitForFreeSlotAt(nextSequence, dependentSequences, getMinGatingSequenceThreadLocal());

    return nextSequence;
}

void AbstractMultithreadedClaimStrategy::setSequence(const int64_t sequence, SequenceArray &dependentSequences)
{
    claimSequence.set(sequence);
    waitForFreeSlotAt(sequence, dependentSequences, getMinGatingSequenceThreadLocal());
}

int64_t AbstractMultithreadedClaimStrategy::checkAndIncrement(int availableCapacity, int delta, SequenceArray &gatingSequences)
{
    for (;;)
    {
        int64_t sequence = claimSequence.get();
        if (hasAvailableCapacity(sequence, availableCapacity, gatingSequences)) {
            int64_t nextSequence = sequence + delta;
            if (claimSequence.compareAndSet(sequence, nextSequence)) return nextSequence;
        }
        else throw InsufficientCapacityException();
    }

}






void AbstractMultithreadedClaimStrategy::waitForFreeSlotAt(const int64_t sequence,
                                                   SequenceArray &dependentSequences,
                                                   PaddedInt64 *minGatingSequence)
{
    int64_t wrapPoint = sequence - bufferSize;
    if (wrapPoint > minGatingSequence->get())
    {
        int64_t minSequence;
        while (wrapPoint > (minSequence = Util::getMinimumSequence(dependentSequences)))
        {
            //std::this_thread::sleep_until(1);
            std::this_thread::yield();
        }

        minGatingSequence->set(minSequence);
    }

}

bool AbstractMultithreadedClaimStrategy::hasAvailableCapacity(int64_t sequence,
                                                      const int availableCapacity,
                                                      SequenceArray &dependentSequences)
{
    int64_t wrapPoint = (sequence + availableCapacity) - bufferSize;
    PaddedInt64 *minGatingSequence =getMinGatingSequenceThreadLocal();
    if (wrapPoint > minGatingSequence->get()) {
        int64_t minSequence = Util::getMinimumSequence(dependentSequences);
        minGatingSequence->set(minSequence);

        if (wrapPoint > minSequence) return false;
    }

    return true;
}

PaddedInt64 *AbstractMultithreadedClaimStrategy::getMinGatingSequenceThreadLocal()
{
    PaddedInt64 *minGatingSequence = minGatingSequenceThreadLocal->get(std::this_thread::get_id());
    if (minGatingSequence==nullptr) {
        minGatingSequence = new PaddedInt64();
        garbage.add(minGatingSequence);
        minGatingSequenceThreadLocal->put(std::this_thread::get_id(), *minGatingSequence);
    }
    return minGatingSequence;
}

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
#include "multiThreadedClaimStrategy.h"
#include "util.h"
#include "insufficientCapacityException.h"

using namespace disruptor;

MultiThreadedClaimStrategy::MultiThreadedClaimStrategy(const int bufferSize, const int pendingBufferSize) : AbstractMultithreadedClaimStrategy(bufferSize)
{
    if (Util::bitCount(pendingBufferSize) != 1) throw hba::IllegalArgumentException("pendingBufferSize must be a power of 2, was: " + pendingBufferSize);
    pendingPublication = new hba::atomic::AtomicInt64Array(pendingBufferSize);
    pendingMask = pendingBufferSize - 1;
}

MultiThreadedClaimStrategy::~MultiThreadedClaimStrategy()
{
    delete pendingPublication;
}



void MultiThreadedClaimStrategy::serialisePublishing(const int64_t sequence, AtomicInt64 &cursor, const int batchSize)
{
    int counter = RETRIES;
    while (sequence - cursor.get() > pendingPublication->length())  {
        if (--counter == 0)  {
            std::this_thread::yield();
            counter = RETRIES;
        }
    }

    int64_t expectedSequence = sequence - batchSize;
    for (int64_t pendingSequence = expectedSequence + 1; pendingSequence < sequence; pendingSequence++) {
        pendingPublication->set(pendingSequence & pendingMask, pendingSequence);
    }
    pendingPublication->set((int) sequence & pendingMask, sequence);

    int64_t cursorSequence = cursor.get();
    if (cursorSequence >= sequence) return;

    expectedSequence = expectedSequence > cursorSequence ? expectedSequence : cursorSequence;
    int64_t nextSequence = expectedSequence + 1;
    while (cursor.compareAndSet(expectedSequence, nextSequence)) {
        expectedSequence = nextSequence;
        nextSequence++;
        if (pendingPublication->get((int) nextSequence & pendingMask) != nextSequence) break;
    }
}


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
#include "sequencer.h"

using namespace disruptor;

Sequencer::Sequencer(ClaimStrategy *claimStrategy, WaitStrategy *waitStrategy) : cursor(hba::atomic::AtomicInt64::INITIAL_CURSOR_VALUE)
{
    gatingSequences = nullptr;
    this->claimStrategy = claimStrategy;
    this->waitStrategy = waitStrategy;
}

Sequencer::~Sequencer()
{
    //TODO: I'm not sure if the gatingSequences should be deleted here
    //if (nullptr != gatingSequences) delete gatingSequences; //comming from Util::getSequencesFor
}

int64_t Sequencer::next()
{
    if (nullptr == gatingSequences)
    {
        throw hba::NullPointerException("gatingSequences must be set before claiming sequences");
    }

    return claimStrategy->incrementAndGet(*gatingSequences);
}

int64_t Sequencer::tryNext(int requiredCapacity)
{
    if (nullptr == gatingSequences)
    {
        throw hba::NullPointerException("gatingSequences must be set before claiming sequences");
    }

    if (requiredCapacity < 1)
    {
        throw hba::IllegalArgumentException("Required capacity must be greater than 0");
    }

    return claimStrategy->checkAndIncrement(requiredCapacity, 1, *gatingSequences);
}

int64_t Sequencer::claim(const int64_t sequence)
{
    if (nullptr == gatingSequences)
    {
        throw hba::NullPointerException("gatingSequences must be set before claiming sequences");
    }

    claimStrategy->setSequence(sequence, *gatingSequences);

    return sequence;
}

int64_t Sequencer::remainingCapacity()
{
    int64_t consumed = Util::getMinimumSequence(*gatingSequences);
    int64_t produced = cursor.get();
    return getBufferSize() - (produced - consumed);
}

void Sequencer::publish(const int64_t sequence)
{
    publish(sequence, 1);
}

void Sequencer::forcePublish(const int64_t sequence)
{
    cursor.set(sequence);
    waitStrategy->signalAllWhenBlocking();

}

void Sequencer::publish(const int64_t sequence, const int batchSize)
{
    claimStrategy->serialisePublishing(sequence, cursor, batchSize);
    waitStrategy->signalAllWhenBlocking();
}


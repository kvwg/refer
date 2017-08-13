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
#include "processingSequenceBarrier.h"
#include "alertException.h"

using namespace disruptor;

ProcessingSequenceBarrier::ProcessingSequenceBarrier(WaitStrategy *waitStrategy, AtomicInt64 *cursorSequence, SequenceArray &dependentSequences)
{
    alerted = false;

    this->waitStrategy = waitStrategy;
    this->cursorSequence = cursorSequence;
    this->dependentSequences = &dependentSequences;
}

ProcessingSequenceBarrier::ProcessingSequenceBarrier(ProcessingSequenceBarrier&& barrierToCopy)
{
    waitStrategy = barrierToCopy.waitStrategy;
    barrierToCopy.waitStrategy = {};
    cursorSequence = barrierToCopy.cursorSequence;
    barrierToCopy.cursorSequence = {};
    dependentSequences = barrierToCopy.dependentSequences;
    barrierToCopy.dependentSequences = {};
}

ProcessingSequenceBarrier::~ProcessingSequenceBarrier()
{
    //TODO: Not sure I have to delete this
    delete dependentSequences; // comming from Util::getSequencesFor
}

int64_t ProcessingSequenceBarrier::waitFor(const int64_t sequence)
{
    checkAlert();

    return waitStrategy->waitFor(sequence, *cursorSequence, *dependentSequences, *this);
}


void ProcessingSequenceBarrier::alert()
{
    alerted = true;
    waitStrategy->signalAllWhenBlocking();
}

void ProcessingSequenceBarrier::checkAlert()
{
    if (alerted)
    {
        throw AlertException();
    }
}

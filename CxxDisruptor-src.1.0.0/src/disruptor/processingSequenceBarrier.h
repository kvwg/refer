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
#ifndef PROCESSINGSEQUENCEBARRIER_H
#define PROCESSINGSEQUENCEBARRIER_H

#include "atomicInt64.h"
#include "waitStrategy.h"

namespace disruptor {

    /**
     * @brief Implements SequenceBarrier
     * Handed out for gating EventProcessors on a cursor sequence and optional dependent EventProcessors
     */
    class ProcessingSequenceBarrier : public SequenceBarrier
    {
    private:
        WaitStrategy *waitStrategy;
        AtomicInt64 *cursorSequence;
        SequenceArray *dependentSequences;
        volatile bool alerted;

    public:
        ProcessingSequenceBarrier(WaitStrategy *waitStrategy, AtomicInt64 *cursorSequence, SequenceArray &dependentSequences);
        ProcessingSequenceBarrier(ProcessingSequenceBarrier&& barrierToCopy);
        ~ProcessingSequenceBarrier();

        int64_t waitFor(const int64_t sequence);
        //int64_t waitFor(final int64_t sequence, final int64_t timeout, final TimeUnit units);
        int64_t getCursor() {return cursorSequence->get();}
        bool isAlerted() {return alerted; }
        void alert();
        void clearAlert() {alerted = false; }
        void checkAlert();
    };
}

#endif // PROCESSINGSEQUENCEBARRIER_H

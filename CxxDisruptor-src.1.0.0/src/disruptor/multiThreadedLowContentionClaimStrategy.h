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
#ifndef MULTITHREADEDLOWCONTENTIONCLAIMSTRATEGY_H
#define MULTITHREADEDLOWCONTENTIONCLAIMSTRATEGY_H

#include "abstractMultithreadedClaimStrategy.h"

namespace disruptor {

    /**
     * @brief Inherit AbstractMultithreadedClaimStrategy
     * Strategy to be used when there are multiple publisher threads claiming sequences.
     *
     * This strategy requires sufficient cores to allow multiple publishers to be concurrently claiming sequences and those
     * thread a contented relatively infrequently.
     */

    class MultiThreadedLowContentionClaimStrategy : public AbstractMultithreadedClaimStrategy
    {
    public:
        MultiThreadedLowContentionClaimStrategy(int bufferSize):AbstractMultithreadedClaimStrategy(bufferSize) {}

        void serialisePublishing(const int64_t sequence, AtomicInt64 &cursor, const int batchSize)
        {
            int64_t expectedSequence = sequence - batchSize;
            while (expectedSequence != cursor.get())
            {
                // busy spin
            }

            cursor.set(sequence);
        }
    };

}

#endif // MULTITHREADEDLOWCONTENTIONCLAIMSTRATEGY_H

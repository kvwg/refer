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
#ifndef SEQUENCEBARRIER_H
#define SEQUENCEBARRIER_H

#include "baseDisruptorClass.h"

namespace disruptor {


    /**
     * @brief Interface
     * Coordination barrier for tracking the cursor for publishers and sequence of
     * dependent EventProcessors for processing a data structure
     */
    class SequenceBarrier : public BaseDisruptorClass
    {
    public:
        /**
         * @brief waitFor
         * Wait for the given sequence to be available for consumption.
         *
         * @param sequence to wait for
         * @return the sequence up to which is available
         * @throws AlertException if a status change has occurred for the Disruptor
         */
        virtual int64_t waitFor(int64_t sequence) = 0;

        //TODO: virtual int64_t waitFor(int64_t sequence, int64_t timeout, TimeUnit units) = 0;

        /**
         * @brief getCursor
         * Delegate a call to the Sequencer.getCursor()
         *
         * @return value of the cursor for entries that have been published.
         */
        virtual int64_t getCursor() = 0;

        /**
         * @brief isAlerted
         * The current alert status for the barrier.
         *
         * @return true if in alert otherwise false.
         */
        virtual bool isAlerted() = 0;

        /**
         * @brief alert
         * Alert the EventProcessors of a status change and stay in this status until cleared.
         */
        virtual void alert() = 0;

        /**
         * @brief clearAlert
         * Clear the current alert status.
         */
        virtual void clearAlert() = 0;

        /**
         * @brief checkAlert
         * Check if an alert has been raised and throw an {@link AlertException} if it has.
         *
         * @throws AlertException if alert has been raised.
         */
        virtual void checkAlert() = 0;
    };
}


#endif // SEQUENCEBARRIER_H

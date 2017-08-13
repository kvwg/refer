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
#ifndef UTIL_H
#define UTIL_H

#include <thread>
#include "atomicInt64.h"
#include "sequenceArray.h"
#include "eventProcessorArray.h"

using namespace hba::atomic;

namespace disruptor {

    /**
     * @brief
     * Set of common functions used by the Disruptor
     */
    class Util
    {
    public:
        /**
         * @brief getMinimumSequence
         * Get the minimum sequence from an array of {@link com.lmax.disruptor.Sequence}s.
         *
         * @param sequences to compare.
         * @return the minimum sequence found or Long.MAX_VALUE if the array is empty.
         */
        static int64_t getMinimumSequence(SequenceArray &sequences);

        /**
         * @brief getSequencesFor
         * Get an array of Sequences for the passed EventProcessors
         *
         * @param processors for which to get the sequences
         * @return the array of Sequences, last element is a nullptr to indicate end of array. Note
         *         this array should explicit be deleted by the calling class by "delete [] ..."
         *         to not create a memory leek.
         */
        static SequenceArray* getSequencesFor(EventProcessorArray &procsesors);

        /**
         * @brief bitCount
         * Returns the number of one-bits in the two's complement binary
         * representation of the specified int32 value. This function is
         * sometimes referred to as the population count.
         *
         * @param i
         * @return the number of one-bits in the two's complement binary
         *     representation of the specified int32 value.
         */
        static int bitCount(int32_t i);

        /**
         * @brief bitCount
         * Returns the number of one-bits in the two's complement binary
         * representation of the specified int64 value. This function is
         * sometimes referred to as the population count.
         *
         * @param i
         * @return the number of one-bits in the two's complement binary
         *     representation of the specified int64 value.
         */
        static int bitCount(int64_t i);

        /**
         * @brief setAffinity
         * Set the affinity mask for the given thread.
         *
         * @param handle for thread whose affinity mask is to be set.
         * @param mask the affinity mask for the thread. A thread affinity
         *        mask is a bit vector in which each bit represents a logical
         *        processor that a thread is allowed to run on.
         * @throws ThreadException
         */
        static void setAffinity(std::thread::native_handle_type handle, int64_t mask);

        static int64_t getCurrentThreadAffinity();
    };

}

#endif // UTIL_H

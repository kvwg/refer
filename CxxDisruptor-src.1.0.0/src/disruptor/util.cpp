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
#include <errno.h>
#include <stdio.h>
#include "util.h"
#include "threadException.h"

using namespace disruptor;

int64_t Util::getMinimumSequence(SequenceArray &sequences)
{
    int64_t minimum =  0x7fffffffffffffff; //signed long MAX_VALUE;

    for (int i=0; i<sequences.size(); i++) {
        AtomicInt64 sequence = sequences[i];
        int64_t value = sequence.get();
        minimum = minimum < value ? minimum : value;
    }

    return minimum;
}

SequenceArray* Util::getSequencesFor(EventProcessorArray &procsesors)
{
    SequenceArray sequences(procsesors.size());
    for (int i = 0; i < procsesors.size(); i++) {
        sequences.set(procsesors[i].getSequence(), i);
    }

    return sequences.forward();
}

int Util::bitCount(int32_t i) {
    // HD, Figure 5-2
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);
    return i & 0x3f;
}

int Util::bitCount(int64_t i) {
   // HD, Figure 5-14
   i = i - ((i >> 1) & 0x5555555555555555L);
   i = (i & 0x3333333333333333L) + ((i >> 2) & 0x3333333333333333L);
   i = (i + (i >> 4)) & 0x0f0f0f0f0f0f0f0fL;
   i = i + (i >> 8);
   i = i + (i >> 16);
   i = i + (i >> 32);
   return (int)i & 0x7f;
}

void Util::setAffinity(std::thread::native_handle_type handle, int64_t mask)
{
#if defined(WIN32)
    //TODO: Not sure if this is correct as I have not tested on Windows.
    SetThreadAffinityMask(handle, mask);
    DWORD err = GetLastError();
    if (err!=0) throw hba::ThreadException("Setting the affinityt mask for the given thread failed.");
#elif defined(__linux__)
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
//    for(unsigned int i = 0; i < sizeof(int64_t) * 8; i++) {
//        if (mask & 1) CPU_SET(i, &cpuset);
//        mask >>= 1;
//    }
    for(int i = 0; i < CPU_SETSIZE; i++) {
        if (mask & 1) CPU_SET(i, &cpuset);
        mask >>= 1;
    }
    //See http://man7.org/linux/man-pages/man3/pthread_setaffinity_np.3.html
    int err = pthread_setaffinity_np(handle, sizeof(cpuset), &cpuset);
    // Throw an exception if the returned value is not 0
    switch (err) {
    case 0: return;
    case EFAULT: throw hba::ThreadException("A supplied memory address was invalid.");
    case EINVAL: throw hba::ThreadException("Problems with the passed mask parameter.");
    case ESRCH: throw hba::ThreadException("No thread with the ID thread could be found.");
    default: throw hba::ThreadException("Not known ERROR code was returned from system.");
    }
#else
#warning thread_setaffinity_mask not implemented on this arch!
    throw std::runtime_error("as::thread_setaffinity_mask");
#endif
}

int64_t Util::getCurrentThreadAffinity()
{
    //TODO: do something for Windows
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    //maybe it is more correct to use pthread_getaffinity_np
    int err = sched_getaffinity(0, sizeof(cpu_set_t), &cpuset);
    if (err!=0) throw hba::ThreadException("The system returned an error");
    int64_t retVal = 0;
    for (int i=0; i<CPU_SETSIZE; i++) {
        if (CPU_ISSET(i, &cpuset)) {
            int64_t mask = 1 << i;
            retVal |= mask;
        }
    }
    //int cpu = sched_getcpu(); // Get the actual CPU used by the current thread
    return retVal;
}




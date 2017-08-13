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
 */
#ifndef UTILTEST_H
#define UTILTEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
#include <thread>
#include "util.h"

using namespace disruptor;

class utilTest  : public CxxTest::TestSuite
{
public:
    void testAffinity(void)
    {
        int64_t mask = 4;
        std::thread::native_handle_type handle = pthread_self();

        Util::setAffinity(handle, mask);
        int64_t cpuset = Util::getCurrentThreadAffinity();
        TS_ASSERT_EQUALS(mask, cpuset);

        //Which CPU are we running on?
        int cpu = sched_getcpu();
        int64_t cpuMask = 1 << cpu;
        TS_ASSERT_EQUALS(mask & cpuMask, cpuMask);
    }
};

#endif // UTILTEST_H

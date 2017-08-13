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
#ifndef ATOMICINT32TEST_H
#define ATOMICINT32TEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
#include "atomicInt32.h"

using namespace hba::atomic;

class AtomicInt32Test  : public CxxTest::TestSuite
{
public:
    void testCompareAndSet(void)
    {
        AtomicInt32 atomicInt32(4);
        TS_ASSERT(atomicInt32.compareAndSet(4, 5));
        TS_ASSERT(!atomicInt32.compareAndSet(4, 10));
    }

    void testFetchAndAdd(void)
    {
        AtomicInt32 atomicInt32(4);
        int32_t i32 = atomicInt32.fetchAndAdd(6);
        TS_ASSERT_EQUALS(i32, 4);
        TS_ASSERT_EQUALS(atomicInt32.get(), 10);

        i32 = atomicInt32.fetchAndAdd(0x7fffff00);
        TS_ASSERT_EQUALS(i32, 10);
        TS_ASSERT_EQUALS(atomicInt32.get(), 0x7fffff0a);
    }

    void testOfArithmetic(void)
    {
        AtomicInt32 atomicInt32(4);

        TS_ASSERT_EQUALS(atomicInt32++, 5);
        TS_ASSERT_EQUALS(atomicInt32--, 4);
        atomicInt32 += 6;
        TS_ASSERT_EQUALS(atomicInt32.get(), 10);
        TS_ASSERT_EQUALS(atomicInt32.getAndAdd(10), 10);
        TS_ASSERT_EQUALS(atomicInt32.get(), 20);
        TS_ASSERT_EQUALS(atomicInt32.getAndSet(100), 20);
        TS_ASSERT_EQUALS(atomicInt32.get(), 100);
        AtomicInt32 a = ++atomicInt32;
        TS_ASSERT_EQUALS(a.get(), 100);
        TS_ASSERT_EQUALS(atomicInt32.get(), 101);
    }
};

#endif // ATOMICINT32TEST_H

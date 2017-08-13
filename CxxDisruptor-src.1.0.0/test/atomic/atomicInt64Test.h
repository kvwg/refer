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
#ifndef ATOMICINT64TEST_H
#define ATOMICINT64TEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
#include <thread>
#include <functional>
#include "atomicInt64.h"
#include "threadAble.h"

using namespace hba::atomic;


void threadWork(AtomicInt64 *atomicValue) {
    for (int i=0; i<1000; i++) *atomicValue++;
}

class ThreadRunner : public hba::ThreadAble
{
private:
    AtomicInt64 *atomicValue;
public:
    ThreadRunner(AtomicInt64 * value){atomicValue = value;}
    void run()
    {
        for (int i=0; i<1000; i++)
        {
            (*atomicValue)++;
//            if (i%100==0) CXXTEST_STD(cout) << getId() << " is running" << CXXTEST_STD(endl);
            std::this_thread::yield();
        }
    }
};

class AtomicInt64Test  : public CxxTest::TestSuite
{
public:
    void testCompareAndSet(void)
    {
        AtomicInt64 atomicInt64(4);

        TS_ASSERT(atomicInt64.compareAndSet(4, 5));
        TS_ASSERT(!atomicInt64.compareAndSet(8, 9));
        TS_ASSERT_EQUALS(atomicInt64.get(), 5);

        atomicInt64.set(0x7fffffffffffff00);
        TS_ASSERT(atomicInt64.compareAndSet(0x7fffffffffffff00, 0x7fffffffffffff05));
        TS_ASSERT(!atomicInt64.compareAndSet(4, 0x7fffffffffffff06));
        TS_ASSERT_EQUALS(atomicInt64.get(), 0x7fffffffffffff05);
    }

    void testFetchAndAdd(void)
    {
        AtomicInt64 atomicInt64(4);
        int64_t i64 = atomicInt64.fetchAndAdd(6);
        TS_ASSERT_EQUALS(i64, 4);
        TS_ASSERT_EQUALS(atomicInt64.get(), 10);

        atomicInt64.set(0x7fffffffffffff00);
        i64 = atomicInt64.fetchAndAdd(10);
        TS_ASSERT_EQUALS(i64, 0x7fffffffffffff00);
        TS_ASSERT_EQUALS(atomicInt64.get(), 0x7fffffffffffff0a);

        atomicInt64.set(10);
        i64 = atomicInt64;
        TS_ASSERT_EQUALS(i64, 10);
        i64 = atomicInt64.fetchAndAdd(0x7fffffffffffff00);
        TS_ASSERT_EQUALS(i64, 10);
        TS_ASSERT_EQUALS(atomicInt64.get(), 0x7fffffffffffff0a);
    }

    void testOfArithmetic(void)
    {
        AtomicInt64 atomicInt64(4);

        TS_ASSERT_EQUALS(atomicInt64++, 5);
        TS_ASSERT_EQUALS(atomicInt64--, 4);
        atomicInt64 += 6;
        TS_ASSERT_EQUALS(atomicInt64.get(), 10);
        TS_ASSERT_EQUALS(atomicInt64.getAndAdd(10), 10);
        TS_ASSERT_EQUALS(atomicInt64.get(), 20);
        TS_ASSERT_EQUALS(atomicInt64.getAndSet(100), 20);
        TS_ASSERT_EQUALS(atomicInt64.get(), 100);
        AtomicInt64 a = ++atomicInt64;
        TS_ASSERT_EQUALS(a.get(), 100);
        TS_ASSERT_EQUALS(atomicInt64.get(), 101);
    }

    void testThreading(void)
    {
//        AtomicInt64 atomicInt64;
        AtomicInt64 *atomicInt64 = new AtomicInt64();

        ThreadRunner thread1(atomicInt64);
        ThreadRunner thread2(atomicInt64);
        ThreadRunner thread3(atomicInt64);

        thread1.start();
        thread2.start();
        thread3.start();

        thread1.stop();
        thread2.stop();
        thread3.stop();

        TS_ASSERT_EQUALS(atomicInt64->get(), 3000);
    }
};




#endif // ATOMICINT64TEST_H

#ifndef ATOMICINT64ARRAYTEST_H
#define ATOMICINT64ARRAYTEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
#include <thread>
#include <functional>
#include "atomicInt64Array.h"
#include "threadAble.h"
#include "indexOutOfBoundsException.h"

using namespace hba::atomic;

class AtomicInt64ArrayTest  : public CxxTest::TestSuite
{
public:
    void testSimple(void)
    {
        AtomicInt64Array array(8);
        for (int i=0; i<8; i++) {
            array.set(i, i+1);
        }

        for (int i=0; i<8; i++) {
            TS_ASSERT_EQUALS(array.get(i), i+1);
        }

        TS_ASSERT_THROWS(array.set(100, 100), hba::IndexOutOfBoundsException);
    }

    void testOperators(void)
    {
        AtomicInt64Array array(8);
        for (int i=0; i<8; i++) {
            array.set(i, i+1);
        }
        int64_t i = array[2];
        TS_ASSERT_EQUALS(i, 3);

        array[3] = 100;
        TS_ASSERT_EQUALS(array[3], 100);

        array[3]++;
        i = array[3];
        TS_ASSERT_EQUALS(i, 101);
    }
};

#endif // ATOMICINT64ARRAYTEST_H

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
#ifndef IDENTITYHASHTABLETEST_H
#define IDENTITYHASHTABLETEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
#include "identityHashTable.h"
#include "illegalArgumentException.h"

using namespace hba;

class MyInteger
{
public:
    MyInteger(int val) {value = val;}
    int value;
};

namespace std {
    template <>
    class hash<MyInteger> {
    public :
        size_t operator()(const MyInteger &myInteger ) const {
            return hash<int>()(myInteger.value);
        }
    };
}


class IdentityHashTableTest : public CxxTest::TestSuite
{
public:
    void testAutoResizing(void)
    {
        IdentityHashTable<long> *ptrTable;
        TS_ASSERT_THROWS(ptrTable=new IdentityHashTable<long>(9), IllegalArgumentException);

        IdentityHashTable<int> testTable(8);
        int values[10];
        for (int i=0; i<10; i++) {
            values[i] = i;
            int k = testTable.set(values[i]);
            int *v = testTable.get(k);
            TS_ASSERT(*v == values[i]);
        }
        TS_ASSERT(testTable.getLength() > 8);
        CXXTEST_STD(cout) << "Table length: "<< testTable.getLength() << CXXTEST_STD(endl);

        int l = testTable.getLength();
        for (int i=0; i<8; i++) {
            testTable.remove(i) ;
        }
        TS_ASSERT(testTable.getLength()<l);
    }

    void testIterator(void)
    {
        IdentityHashTable<MyInteger> testTable;
        for (int i=0; i<10; i++) {
            MyInteger *myInteger = new MyInteger(i);
            testTable.set(*myInteger);
        }

        int count = 0;
        MyInteger *ptrInteger = testTable.iteratorFirst();
        while (ptrInteger != nullptr) {
            ptrInteger = testTable.iteratorNext();
            count++;
        }
        TS_ASSERT(count == 10);
    }

};

#endif // IDENTITYHASHTABLETEST_H

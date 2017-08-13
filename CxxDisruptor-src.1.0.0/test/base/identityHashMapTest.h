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
#ifndef IDENTITYHASHMAPTEST_H
#define IDENTITYHASHMAPTEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
#include "identityHashMap.h"
#include "illegalArgumentException.h"

using namespace hba;

class IdentityHashMapTest : public CxxTest::TestSuite
{
public:
    void testX(void)
    {
        IdentityHashMap<int, long> *ptrMap;
        //TS_ASSERT_THROWS(ptrMap=new IdentityHashMap<int, long>(9), IllegalArgumentException);
        try {
            ptrMap = new IdentityHashMap<int, long>(9);
            TS_FAIL("No Exceptions was thrown!");
        } catch (IllegalArgumentException ex) {

        }

        IdentityHashMap<int, long> testMap(8);
        long values[10];
        for (int i=0; i<10; i++) {
            values[i] = i;
            testMap.put(i, values[i]);
            long *v = testMap.get(i);
            TS_ASSERT(*v == values[i]);
        }

        for (int i=0; i<8; i++) {
            long *v = testMap.remove(i);
            TS_ASSERT(v != nullptr);
        }
        TS_ASSERT(testMap.get(5) == nullptr);
    }

};

#endif // IDENTITYHASHMAPTEST_H

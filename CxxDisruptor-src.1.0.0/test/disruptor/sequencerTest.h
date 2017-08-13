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
/*
 * Unit test for the Sequence class
 */
#ifndef SEQUENCERTEST_H
#define SEQUENCERTEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
//#include <cxxtest/ErrorPrinter.h>
//#include <iostream>

#include "singleThreadedClaimStrategy.h"
#include "yieldingWaitStrategy.h"
#include "sequencer.h"
#include "insufficientCapacityException.h"
#include "sequenceArray.h"

using namespace disruptor;

class SequenceTest  : public CxxTest::TestSuite
{
private:
    ClaimStrategy *claimStrategy;
    WaitStrategy *waitStrategy;

public:
    void setUp()
    {
        claimStrategy = new SingleThreadedClaimStrategy(16);
        waitStrategy = new YieldingWaitStrategy();
    }

    void tearDown() {
        delete claimStrategy;
        delete waitStrategy;
    }

    void testNext(void)
    {
        CXXTEST_STD(cout) << "Test: testNext started." << CXXTEST_STD(endl);
        disruptor::Sequencer sequencer = disruptor::Sequencer(claimStrategy, waitStrategy);

        long next = -1;

        TS_ASSERT_THROWS(next = sequencer.next(), hba::NullPointerException);
        TS_ASSERT_EQUALS(next, -1);

        SequenceArray gatingSequences(2, new hba::atomic::AtomicInt64, new hba::atomic::AtomicInt64);
        sequencer.setGatingSequences(gatingSequences);

        next = sequencer.next();
        TS_ASSERT_EQUALS(next, 0);
        next = sequencer.next();
        TS_ASSERT_EQUALS(next, 1);
    }

    void testTryNext(void)
    {
        CXXTEST_STD(cout) << "Test: testTryNext started." << CXXTEST_STD(endl);
        disruptor::Sequencer sequencer = disruptor::Sequencer(claimStrategy, waitStrategy);

        SequenceArray gatingSequences(2, new hba::atomic::AtomicInt64, new hba::atomic::AtomicInt64);
        sequencer.setGatingSequences(gatingSequences);

        long next = -1;

        TS_ASSERT_THROWS(next = sequencer.tryNext(-2), hba::IllegalArgumentException);
        TS_ASSERT_EQUALS(next, -1);

        TS_ASSERT_THROWS(next = sequencer.tryNext(1000), InsufficientCapacityException);
        TS_ASSERT_EQUALS(next, -1);

        next = sequencer.tryNext(3);
        TS_ASSERT_EQUALS(next, 0);
    }

    void testNewBarrier()
    {
        CXXTEST_STD(cout) << "Test: testNewBarrier started." << CXXTEST_STD(endl);
        disruptor::Sequencer sequencer = disruptor::Sequencer(claimStrategy, waitStrategy);

        SequenceArray gatingSequences(2);
        sequencer.setGatingSequences(gatingSequences);
        sequencer.forcePublish(3);

//        ProcessingSequenceBarrier b = sequencer.newBarrierTest(*(gatingSequences.forward()));
        ProcessingSequenceBarrier barrier = sequencer.newBarrierTest(*(gatingSequences.forward()));
//        SequenceBarrier barrier = sequencer.newBarrierTest(gatingSequences);
        int64_t c = barrier.getCursor();
        TS_ASSERT_EQUALS(c, 3);
    }
};

#endif // SEQUENCERTEST_H

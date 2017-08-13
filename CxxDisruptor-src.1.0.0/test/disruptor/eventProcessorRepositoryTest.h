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
#ifndef EVENTPROCESSORREPOSITORYTEST_H
#define EVENTPROCESSORREPOSITORYTEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
#include <thread>
#include "eventProcessorRepository.h"
#include "yieldingWaitStrategy.h"
#include "eventHandler.h"
#include "processingSequenceBarrier.h"
#include "eventProcessor.h"
#include "getTicks.h"

using namespace disruptor;

class TestClass{};

class TestEventHandler : public EventHandler<TestClass>
{
private:
    size_t hashValue;
public:
//    TestEventHandler()
//    {
//        hashValue = (size_t)get_ticks();
//        std::this_thread::yield(); // to be sure that the ticks count a bit
//    }

    void onEvent(TestClass &event, long sequence, bool endOfBatch)
    {

    }

    void onStart()
    {
    }

    void onShutdown()
    {
    }
    //size_t hashCode() const {return hashValue;}
    std::size_t hashCode() const {return std::hash<const void *>()(this);}

};

class TestEventProcessor : public EventProcessor
{
private:
    int id;
    hba::atomic::AtomicInt64 sequence;
    size_t hashValue;

public:
    TestEventProcessor(int id)
    {
        this->id = id;
        hashValue = (size_t)get_ticks();
        std::this_thread::yield(); // to be sure that the ticks count a bit
    }

    int getId() {return id;}

    hba::atomic::AtomicInt64 *getSequence() {return &sequence;}

    void halt() {}

    void run() {}

    std::size_t hashCode() const {return hashValue;}

};



class EventProcessorRepositoryTest : public CxxTest::TestSuite
{
public:
    void testAdd(void)
    {
        hba::atomic::AtomicInt64 cursorSequence;
        YieldingWaitStrategy waitStrategy;
        SequenceArray dependentSequences(0);
        ProcessingSequenceBarrier barrier(&waitStrategy, &cursorSequence, dependentSequences);

        TestEventHandler eventHandler1;
        TestEventHandler eventHandler2;
        TestEventHandler nobodysEventHandler;

        EventProcessorRepository<TestClass> testRepo;
        TestEventProcessor processor1(1);
        TestEventProcessor processor2(2);
        TestEventProcessor processor3(3);

        testRepo.add(processor1, eventHandler1, barrier);
        testRepo.add(processor2);
        testRepo.add(processor3, eventHandler2, barrier);

        TS_ASSERT_THROWS(testRepo.getEventProcessorFor(nobodysEventHandler), hba::IllegalArgumentException);
        EventProcessor *ptrProcessor = testRepo.getEventProcessorFor(eventHandler1);
        TS_ASSERT(((TestEventProcessor*)ptrProcessor)->getId()==1);

        EventProcessor *barrierEventProcessors[1];
        barrierEventProcessors[0] = &processor2;
        testRepo.unMarkEventProcessorsAsEndOfChain(barrierEventProcessors, 1);
        TestEventProcessor **lastProcessorsInChain = (TestEventProcessor **)testRepo.getLastEventProcessorsInChain();
        TestEventProcessor *aLastProcess;
        int count = 0;
        do {
            aLastProcess = lastProcessorsInChain[count++];
        } while (aLastProcess != nullptr);
        TS_ASSERT(count == 3);

        SequenceBarrier *ptrBarrier = testRepo.getBarrierFor(eventHandler1);
        TS_ASSERT(ptrBarrier != nullptr);
        ptrBarrier = testRepo.getBarrierFor(nobodysEventHandler);
        TS_ASSERT(ptrBarrier == nullptr);
    }
};


#endif // EVENTPROCESSORREPOSITORYTEST_H

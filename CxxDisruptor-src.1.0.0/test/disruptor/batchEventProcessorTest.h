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
#ifndef BATCHEVENTPROCESSORTEST_H
#define BATCHEVENTPROCESSORTEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
#include <iostream>
#include "batchEventProcessor.h"
#include "processingSequenceBarrier.h"
#include "threadAble.h"

using namespace disruptor;

class TestClass : public EventInitializer<TestClass>
{
private:
    const char *message;

public:
    TestClass() {
        message = nullptr;
    }

    void setMessage(const char *msg) {message = msg;}
    const char* getMessage() {return message;}

    void init(TestClass &objectToInit) {

    }
};

class TestEventHandler : public EventHandler<TestClass>
{
public:
    int called = 0;

    void onEvent(TestClass &event, long sequence, bool endOfBatch)
    {
        called++;
        std::cout << "Got an event!:" << std::endl;
        std::cout << "- Sequence=" << sequence << ". Message=\"" << event.getMessage() << "\"." << std::endl;
    }

    void onStart()
    {
    }

    void onShutdown()
    {
    }


    size_t hashCode() const {
        return std::hash<const void *>()(this);
    }


};

class TestThread : public hba::ThreadAble
{
private:
    BatchEventProcessor<TestClass> *eventProcessor;

public:
    TestThread(BatchEventProcessor<TestClass> *eventProcessor) {
        this->eventProcessor = eventProcessor;
    }

    void stop() {
        eventProcessor->halt();
        hba::ThreadAble::stop();
    }

    void run() {
        eventProcessor->run();
    }
};

class BatchEventProcessorTest : public CxxTest::TestSuite
{
private:
    BatchEventProcessor<TestClass> *eventProcessor;
    TestClass *testClassFactory;
    RingBuffer<TestClass> *ringBuffer;
    hba::atomic::AtomicInt64 *gatingSequence;
    EventProcessor **barrierEventProcessors;
    SequenceBarrier *sequenceBarrier;
    TestEventHandler *eventHandler;


public:
    void setUp()
    {
        testClassFactory = new TestClass();
        ringBuffer = new RingBuffer<TestClass>(*testClassFactory, 0x100);
        SequenceArray gatingSequences(1);
        gatingSequences[0] = -1;
        ringBuffer->setGatingSequences(gatingSequences);
        sequenceBarrier = ringBuffer->newBarrier(*(Util::getSequencesFor(*(new EventProcessorArray(0)))));
        eventHandler = new TestEventHandler();
        eventProcessor = new BatchEventProcessor<TestClass>(ringBuffer, sequenceBarrier, eventHandler);
    }

    void tearDown()
    {
        delete eventProcessor;
        delete eventHandler;
        delete barrierEventProcessors;
        delete gatingSequence;
        delete ringBuffer;
        delete testClassFactory;
    }

    void testHash(void)
    {

        BatchEventProcessor<TestClass> *ptrBatchEventProcessor = eventProcessor;

        size_t hashCode1 = eventProcessor->hashCode();
        size_t hashCode2 = ptrBatchEventProcessor->hashCode();
        TS_ASSERT(hashCode1 == hashCode2);
    }

    void testStartHalt(void)
    {
        TestThread thread(eventProcessor);
        thread.start();
        std::this_thread::sleep_for(std::chrono::seconds(1));

        RingBuffer<TestClass> *ringBuffer = eventProcessor->getRingBuffer();
        long sequence = ringBuffer->next();
        TestClass *event = ringBuffer->get(sequence);
        event->setMessage("Hi there");
        ringBuffer->publish(sequence);

        thread.stop();
        TS_ASSERT(eventHandler->called == 1);
    }
};

#endif // BATCHEVENTPROCESSORTEST_H

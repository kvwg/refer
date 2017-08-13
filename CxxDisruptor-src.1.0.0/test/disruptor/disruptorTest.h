#ifndef DISRUPTORTEST_H
#define DISRUPTORTEST_H

//#define CXXTEST_HAVE_STD // Use the standard library.
#define CXXTEST_HAVE_EH // Use exception handling.
#define CXXTEST_ABORT_TEST_ON_FAIL // Abort tests on failed asserts
//#define CXXTEST_DEFAULT_ABORT -1 // The default value of the dynamic abort on fail flag.

#include <cxxtest/TestSuite.h>
#include "disruptor.h"
#include "singleThreadedClaimStrategy.h"
#include "multiThreadedLowContentionClaimStrategy.h"
#include "yieldingWaitStrategy.h"
#include "getTicks.h"

using namespace disruptor;

class TestEvent : public EventInitializer<TestEvent>
{
private:
    const char *message;

public:
    TestEvent() {
        message = nullptr;
    }

    void setMessage(const char *msg) {message = msg;}
    const char* getMessage() {return message;}

    void init(TestEvent &objectToInit)
    {
        message = "Initialize object!";
//        std::cout << message << std::endl;
    }
};


class TestEventHandler : public EventHandler<TestEvent>
{
private:
    const char *name;

public:
    int called = 0;
    tick_type ticks = 0;

    TestEventHandler(const char *name) {
        this->name = name;
    }

    void onEvent(TestEvent &event, long sequence, bool endOfBatch)
    {
        called++;
        ticks = get_ticks();
        std::cout << name << " - Got an event!:" << std::endl;
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



class DisruptorTest : public CxxTest::TestSuite
{
public:
    void testDisrupter(void)
    {
        TestEventHandler testEventHandler1("EventHandler 1");
        TestEventHandler testEventHandler2("EventHandler 2");
        TestEventHandler testEventHandler3("EventHandler 3");


        TestEvent eventInitializer;
        //SingleThreadedClaimStrategy claimStrategy(8);
        MultiThreadedLowContentionClaimStrategy claimStrategy(8);
        YieldingWaitStrategy waitStrategy;
        Disruptor<TestEvent> *disruptor = new Disruptor<TestEvent>(eventInitializer, &claimStrategy, &waitStrategy);
        //Disruptor<TestEvent> *disruptor = new Disruptor<TestEvent>(eventInitializer, 8);
        //disruptor->handleEventsWith(testEventHandlers1, 2)->then(testEventHandlers2, 1);
        //disruptor->handleEventsWith(testEventHandlers2, 1);
        disruptor->handleEventsWith(2, &testEventHandler1, &testEventHandler2)->then(1, &testEventHandler3);

        CXXTEST_STD(cout) << "Start Disruptor." << CXXTEST_STD(endl);
        RingBuffer<TestEvent> *ringBuffer = disruptor->start();
        std::this_thread::sleep_for(std::chrono::microseconds(500));

        for (int i=0; i<10; i++)
            setMessage(ringBuffer,"Hi there " + i);

        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        CXXTEST_STD(cout) << "Halt Disruptor." << CXXTEST_STD(endl);
        disruptor->halt();

        TS_ASSERT(testEventHandler3.ticks > testEventHandler1.ticks);
        TS_ASSERT(testEventHandler3.ticks > testEventHandler2.ticks);

        delete disruptor;
    }

    void setMessage(RingBuffer<TestEvent> *ringBuffer, const char * mesg)
    {
        int64_t sequence = ringBuffer->next();
        TestEvent *event = ringBuffer->get(sequence);
        event->setMessage(mesg);
        ringBuffer->publish(sequence);
    }
};

#endif // DISRUPTORTEST_H

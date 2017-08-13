#include <iostream>
#include <chrono>

#include <sys/time.h>
#include <atomic>
#include <cstdint>
#include <string.h>
#include "atomicInt64.h"
#include "getTicks.h"

#include "disruptor.h"
#include "singleThreadedClaimStrategy.h"
#include "yieldingWaitStrategy.h"
#include "atomicBool.h"


using namespace std;

//#define INTERATIONS 10
#define NUMBER_OF_EVENTS_TO_PUBLISH 10000000
#define RINGBUFFER_SIZE 0x1000

//Use milliseconds
#define USE_MS true
//Use microseconds
#define USE_US true

/*
 * Event: The data structure there fill the Ringbuffer and is claimed
 * by the producer and passed to the consummers.
 */
class MyEvent : public disruptor::EventInitializer<MyEvent>
{
private:
    hba::atomic::AtomicBool used;
    char message[1024];

public:
    std::chrono::high_resolution_clock::time_point inDisrupter;
    std::chrono::high_resolution_clock::time_point outDisrupter;

    MyEvent() : used(false)
    {
        message[0] = '\0';
    }

    void setMessage(const char *msg) {
        strcpy(message, msg);
    }
    const char* getMessage() {return message;}

    bool setUsed() {return used.compareAndSet(false, true);}

    void setUnused() { used.set(false);}

    void init(MyEvent &objectToInit) {
        sprintf(message, "Initialize object!");
//        std::cout << message << std::endl;
    }
};

/*
 * Event hanler of MyEvents, this is the consumer of events.
 */
class MyEventHandler : public disruptor::EventHandler<MyEvent>
{
private:
    const char *name;
    int number;
    bool useUnused;

public:
    std::chrono::high_resolution_clock::time_point firstEvent;
    std::chrono::high_resolution_clock::time_point lastEvent;
    int64_t maxLatency = 0;
    int64_t minLatency = 0x7fffffffffffffff;
    int64_t numberOfEvents = 0;
    int64_t affinityMask = 0;
    int cpu = 0;

    MyEventHandler(const char *name, const int number, const bool useUnused)
    {
        firstEvent = lastEvent = std::chrono::system_clock::time_point::min();
        this->name = name;
        this->number = number;
        this->useUnused = useUnused;
    }
    
    MyEventHandler(const char *name, const int number, const bool useUnused, int64_t affinityMask) :MyEventHandler(name, number,useUnused)
    {
        this->affinityMask = affinityMask;
    }

    const char* getName() {return name;}

    //Is called every time a new event is published
    void onEvent(MyEvent &event, long sequence, bool endOfBatch)
    {
        if (useUnused && !event.setUsed()) return;
        if (number==1) event.inDisrupter = std::chrono::high_resolution_clock::now();
        if (number==4) {
            event.outDisrupter = std::chrono::high_resolution_clock::now();
            int64_t l = std::chrono::duration_cast<std::chrono::microseconds>(event.outDisrupter - event.inDisrupter).count();
            if (l > maxLatency) maxLatency = l;
            if (l < minLatency && l>0) minLatency = l;
        }

        if (std::chrono::duration_cast<std::chrono::nanoseconds>(firstEvent-std::chrono::system_clock::time_point::min()).count()==0)
                firstEvent = std::chrono::high_resolution_clock::now();
        lastEvent = std::chrono::high_resolution_clock::now();
        numberOfEvents++;
    }

    //Stuff todo before we are ready to handle events, on the Event Handler thread.
    void onStart()
    {
        if (affinityMask > 0) {
            std::thread::native_handle_type handle = pthread_self();
            disruptor::Util::setAffinity(handle, affinityMask);
        }
    }

    //Stuff todo before the Event Handler thre dies
    void onShutdown()
    {
        cpu = sched_getcpu();
    }


    //Hash code for the actual object = it's pointer.
    size_t hashCode() const {
        return std::hash<const void *>()(this);
    }
};

/*
 * Helper function to printe timestamps
 */
void printTime(const char* text, std::chrono::duration<long, std::ratio<1l, 1000000000l>> time)
{
    if (USE_MS) {
        std::cout << text << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " ms." << std::endl;
    }
    else if (USE_US) {
        std::cout << text << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << " us." << std::endl;
    }
    else {
        std::cout << text << std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() << " ns." << std::endl;
    }
}

/*
 * Helper function to printe timestamps
 */
void printDiffTime(const char* text, std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point stop)
{
    auto diff = stop-start;
    printTime(text, diff);
}


/*
 * Helper function to print information abourt the invloved Event handlers
 */
void printEventHandlerInfo(MyEventHandler &eventHandler)
{
    std::cout << eventHandler.getName() << std::endl;
    std::cout << "- Runned on CPU " << eventHandler.cpu << " with affinity mask: " << eventHandler.affinityMask << std::endl;
    std::cout << "- Did " << eventHandler.numberOfEvents << " events" << std::endl;
    printDiffTime("- in ", eventHandler.firstEvent, eventHandler.lastEvent);
}





//MAIN!!!!!!!!!!!!!!!!!!!!!!!!!
int main(){
    std::cout << "Setting-up the Disruptor." << std::endl;
    MyEvent eventInitializer;
    disruptor::SingleThreadedClaimStrategy claimStrategy(RINGBUFFER_SIZE);
    disruptor::YieldingWaitStrategy waitStrategy;
    disruptor::Disruptor<MyEvent> disruptor(eventInitializer, &claimStrategy, &waitStrategy);

    std::cout << "Setting-up Event Handlers" << std::endl;
    MyEventHandler eventHandler1("Event Handler 1", 1, false, 1);
    MyEventHandler eventHandler2("Event Handler 2", 2, true, 2);
    MyEventHandler eventHandler3("Event Handler 3", 3, true, 4);
    MyEventHandler eventHandler4("Event Handler 4", 4, false, 8);

    // An event is first handler by eventHandler1, then by eventHandler2 and eventHandler3 in parallel and then by eventHandler4
    // Note: Each Event handler will run on its own thread controlled by the disruptor.
    disruptor.handleEventsWith(1, &eventHandler1)->then(2, &eventHandler2, &eventHandler3)->then(1, &eventHandler4);

    std::cout << "Start the Disruptor." << std::endl;
    disruptor::RingBuffer<MyEvent> *ringBuffer = disruptor.start();
    std::this_thread::sleep_for(std::chrono::microseconds(500)); //Let the Disruptor threads start.

    std::cout << "Start to fire messages." << std::endl;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    //START OF PRODUCER ALGORITHM:
    //The main function is the actual producer of events:
    for (int i=0; i<NUMBER_OF_EVENTS_TO_PUBLISH; i++) {
        //Claim a sequence (index in the Ringbuffer)
        int64_t sequence = ringBuffer->next();
        //Get the event container from the Ringbuffer for the claimed sequnce
        MyEvent *event = ringBuffer->get(sequence);

        // Fill in new data to the claimed event
        event->setUnused();
        char messg[1024];
        *messg = '\0';
        //sprintf(messg, "Messege # %i",i); //This slow down the whole process, it is a bottelneck. DON'T DO THAT if you want to be fast!
        event->setMessage(messg);

        //Publish the event (tell the first consummers there is a new event = start the message process).
        ringBuffer->publish(sequence);
    }
    //END OF PRODUCER ALGORITHM:

    std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::microseconds(1000)); //Let the Event Handlers finish there work

    std::cout << "Halt the Disruptor." << std::endl;
    disruptor.halt();

    std::cout << std::endl;
    std::cout << "The main loop (producer) was active in:" << std::endl;
    printDiffTime("- ", start, stop);
    std::cout << std::endl;

    printEventHandlerInfo(eventHandler1);
    printEventHandlerInfo(eventHandler2);
    printEventHandlerInfo(eventHandler3);
    printEventHandlerInfo(eventHandler4);
    std::cout << std::endl;

    printDiffTime("Total time: ", eventHandler1.firstEvent, eventHandler4.lastEvent);
    double diffT = std::chrono::duration_cast<std::chrono::milliseconds>(eventHandler4.lastEvent - eventHandler1.firstEvent).count();
    double x;
    if (diffT == 0) {
        //std::cout << "Something is wrong here: handler 1 first event: " << std::chrono::time_point_cast<std::chrono::microseconds>(eventHandler1.firstEvent);// << " handler 4 last event: " <<  std::chrono::duration_cast<std::chrono::milliseconds>(eventHandler4.lastEvent).count() << std::endl;
        x = 0;
    }
    else x = 1000*(NUMBER_OF_EVENTS_TO_PUBLISH/diffT);
    std::cout.precision(15);
    std::cout << "The Disruptor did: " << x << " events/sec." << std::endl;
    std::cout << "With a max latency = " << eventHandler4.maxLatency << " us." << std::endl;
    std::cout << "and a min latency = " << eventHandler4.minLatency << " us." << std::endl;
}

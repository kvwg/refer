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
 *
 * This code is a porting, from Java to C++, of the Disruptor pattern
 * developed by LMAX. The original Java code can be found at:
 *
 * http://code.google.com/p/disruptor/
 */
#ifndef THREADEXECUTOR_H
#define THREADEXECUTOR_H

#include <thread>
#include "eventProcessor.h"
#include "atomicBool.h"

namespace disruptor {
    /**
     * @brief
     * Encapsulate an EventProcessor in a thread.
     */
    class ThreadExecutor : public BaseDisruptorClass
    {
    private:
        EventProcessor *eventProcessor;
        std::thread myThread;
        hba::atomic::AtomicBool started;

        void run()
        {
            eventProcessor->run();
        }

    public :
        ThreadExecutor(EventProcessor *eventProcessor) : started(false)
        {
            this->eventProcessor = eventProcessor;
        }

        ~ThreadExecutor()
        {
            //TODO: This is risky as stop can block and the delte will never return
            //if (started.get()) stop();
        }

        /**
         * @brief start
         * Start thread.
         */
        void start()
        {
            started.set(true);
            myThread = std::thread(&ThreadExecutor::run, this);
        }

        /**
         * @brief stop
         * Stop thread. Will wait for the thread to join with the calling thread.
         */
        void stop()
        {
            started.set(false);
            eventProcessor->halt();
            myThread.join();
        }


    };

}

#endif // THREADEXECUTOR_H

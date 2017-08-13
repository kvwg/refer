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
#ifndef THREADABLE_H
#define THREADABLE_H

#include <atomic>
#include <thread>

namespace hba {

class ThreadAble
{
public:
    ThreadAble() : stopping(), myThread() { }
    virtual ~ThreadAble() { try { stop(); } catch(...) { /*??*/ } }

    //ThreadAble(Runnable const&) = delete; //non-copyable
    ThreadAble& operator =(ThreadAble const&) = delete; //non-copyable

    std::thread::id getId() {return myThread.get_id();}

    virtual void stop() { stopping = true; myThread.join(); }
    void start() { myThread = std::thread(&ThreadAble::run, this); }

protected:
    virtual void run() = 0;
    std::atomic<bool> stopping;

private:
    std::thread myThread;
};

}

#endif // THREADABLE_H

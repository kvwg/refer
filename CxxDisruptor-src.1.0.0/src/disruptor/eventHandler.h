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
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <functional>
#include "baseDisruptorClass.h"

namespace disruptor {

    /**
     * @brief
     * Callback interface to be implemented for processing events as they become available in the RingBuffer
     *
     * @see BatchEventProcessor#setExceptionHandler(ExceptionHandler) if you want to handle exceptions propigated out of the handler.
     *
     * @param <T> event implementation storing the data for sharing during exchange or parallel coordination of an event.
     */
    template <class T>
    class EventHandler : public BaseDisruptorClass
    {
    public:
        /**
         * @brief onEvent
         * Called when a publisher has published an event to the {@link RingBuffer}
         *
         * @param event published to the {@link RingBuffer}
         * @param sequence of the event being processed
         * @param endOfBatch flag to indicate if this is the last event in a batch from the {@link RingBuffer}
         * @throws Exception if the EventHandler would like the exception handled further up the chain.
         */
        virtual void onEvent(T &event, int64_t sequence, bool endOfBatch) = 0;

        /**
         * @brief lifecycleAwareSOnStart
         * Called once on thread start before first event is available.
         *
         * The LifecyleAware interface can be implemented as a strategy pattern via injection
         * to change this behavior at runtime.
         */
        virtual void onStart() = 0;

        /**
         * @brief lifecycleAwareSOnStart
         * Called once just before the thread is shutdown.
         *
         * The LifecyleAware interface can be implemented as a strategy pattern via injection
         * to change this behavior at runtime.
         */
        virtual void onShutdown() = 0;


        virtual size_t hashCode() const = 0;

    };
}


namespace std {
    template <class T>
    class hash<disruptor::EventHandler<T>> {
    public :
        size_t operator()(const disruptor::EventHandler<T> &eventHandler ) const {
            return eventHandler.hashCode();
        }
    };
}

#endif // EVENTHANDLER_H

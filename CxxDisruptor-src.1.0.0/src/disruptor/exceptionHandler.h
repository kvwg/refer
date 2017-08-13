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
#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <exception>

namespace disruptor {

    /**
     * @brief Interface
     */
    class ExceptionHandler
    {
    public:
        /**
         * @brief handleEventException
         * Strategy for handling uncaught exceptions when processing an event.
         *
         * If the strategy wishes to suspend further processing by the BatchEventProcessor
         * then is should throw a std::exception.
         *
         * @param ex the exception that propagated from the {@link EventHandler}.
         * @param sequence of the event which cause the exception.
         * @param event being processed when the exception occurred.
         */
         virtual void handleEventException(std::exception ex, int64_t sequence, void *event) = 0;

        /**
         * @brief handleOnStartException
         * Callback to notify of an exception during EventHandlers onStart()
         *
         * @param ex throw during the starting process.
         */
        virtual void handleOnStartException(std::exception ex) = 0;

        /**
         * @brief handleOnShutdownException
         * Callback to notify of an exception during EventHandlers onShutdown()
         *
         * @param ex throw during the shutdown process.
         */
        virtual void handleOnShutdownException(std::exception ex) = 0;
    };

}

#endif // EXCEPTIONHANDLER_H

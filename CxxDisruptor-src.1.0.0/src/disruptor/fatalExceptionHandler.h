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
#ifndef FATALEXCEPTIONHANDLER_H
#define FATALEXCEPTIONHANDLER_H

#include "exceptionHandler.h"

namespace disruptor {

    /**
     * @brief Implements ExceptionHandler
     */
    class FatalExceptionHandler : public ExceptionHandler
    {
    public:
        FatalExceptionHandler();

        void handleEventException(std::exception ex, int64_t sequence, void *event);
        void handleOnStartException(std::exception ex);
        void handleOnShutdownException(std::exception ex);
    };

}

#endif // FATALEXCEPTIONHANDLER_H

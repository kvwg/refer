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

#include <iostream>

#include "fatalExceptionHandler.h"

using namespace disruptor;

FatalExceptionHandler::FatalExceptionHandler()
{
    //TODO: atach some kind of logging
}

void FatalExceptionHandler::handleEventException(std::exception ex, int64_t sequence, void *event)
{
    //TODO: log this exseption, not only to std-error
    std::cerr << "EXCEPTION: " << ex.what() << std::endl;
    throw std::exception();
}

void FatalExceptionHandler::handleOnStartException(std::exception ex)
{
    //TODO: log this exseption, not only to std-error
    std::cerr << "EXCEPTION: " << ex.what() << std::endl;
}

void FatalExceptionHandler::handleOnShutdownException(std::exception ex)
{
    //TODO: log this exseption, not only to std-error
    std::cerr << "EXCEPTION: " << ex.what() << std::endl;
}

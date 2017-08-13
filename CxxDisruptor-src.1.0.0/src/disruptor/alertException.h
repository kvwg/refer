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
#ifndef ALERTEXCEPTION_H
#define ALERTEXCEPTION_H

#include <exception>

namespace disruptor {

    /**
     * @brief Exception
     * Used to alert EventProcessors waiting at a SequenceBarrier of status changes.
     *
     * It does not fill in a stack trace for performance reasons.
     */
    class AlertException : public std::exception
    {
    public:
        AlertException(){}
    };

}

#endif // ALERTEXCEPTION_H

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
#ifndef EVENTTRANSLATOR_H
#define EVENTTRANSLATOR_H

/**
 * @brief Interface
 * Implementations translate another data representations into events claimed from the {@link RingBuffer}
 *
 * @param <T> event implementation storing the data for sharing during exchange or parallel coordination of an event.
 */
namespace disruptor {

    template<class T>
    class EventTranslator
    {
    public:
        /**
         * @brief translateTo
         * Translate a data representation into fields set in given event
         *
         * @param event into which the data should be translated.
         * @param sequence that is assigned to event.
         */
        virtual void translateTo(T *event, int64_t sequence) = 0;

    };
}

#endif // EVENTTRANSLATOR_H

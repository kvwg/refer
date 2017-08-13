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
#ifndef ATOMICINT_H
#define ATOMICINT_H

#include <cstdint>

namespace hba {
namespace atomic {

    class AtomicInt64
    {
    private:
        int64_t value = 0;

    public:
        const static int64_t INITIAL_CURSOR_VALUE = -1;

        AtomicInt64(){}
        AtomicInt64(const int64_t initialValue){value = initialValue;}
       // AtomicInt64(AtomicInt64&& value) {this->value = value.value;}

        int64_t get() {return value;}
        void set(const int64_t newValue) {value = newValue;}

        bool compareAndSet(int64_t expect, int64_t update);
        int64_t fetchAndAdd(int64_t increment);

        const AtomicInt64 operator= (AtomicInt64 value) {this->value = value.get();}

        const AtomicInt64 operator++ (); // prefix incrementer
        const AtomicInt64 operator++ (int unused); // postfix incrementer
        const AtomicInt64 operator-- (); // prefix decrementer
        const AtomicInt64 operator-- (int unused); // postfix decrementer

        const int64_t operator+= (int64_t increment);

        const bool operator== (int64_t comparator);
        const bool operator== (int comparator);

        operator int64_t() {return get();}

        int64_t addAndGet(const int64_t increment);
        int64_t getAndAdd(const int64_t newValue);

        int64_t getAndSet(const int64_t newValue);
    };

}
}

#endif // ATOMICINT_H

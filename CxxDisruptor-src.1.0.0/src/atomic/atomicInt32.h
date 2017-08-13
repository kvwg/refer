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

    class AtomicInt32
    {
    private:
        int32_t value = 0;

    public:
        AtomicInt32(){}
        AtomicInt32(const int32_t initialValue){value = initialValue;}
        AtomicInt32(const AtomicInt32 &initialValue) {value = initialValue.value;}

        int get() {return value;}
        void set(const int32_t newValue) {value = newValue;}

        bool compareAndSet(const int32_t expect, const int32_t update);
        int32_t fetchAndAdd(int32_t increment);

        const AtomicInt32 operator++ (); // prefix incrementer
        const AtomicInt32 operator++ (int theFlag); // postfix incrementer
        const AtomicInt32 operator-- (); // prefix decrementer
        const AtomicInt32 operator-- (int theFlag); // postfix decrementer

        const int32_t operator+= (int32_t increment);

        const bool operator== (int32_t comparator);

        int32_t getAndAdd(const int32_t increment);

        int32_t getAndSet(const int32_t newValue);
    };

}
}

#endif // ATOMICINT_H

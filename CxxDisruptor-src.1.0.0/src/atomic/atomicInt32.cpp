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
#include "atomicInt32.h"


using namespace hba::atomic;

bool AtomicInt32::compareAndSet(const int32_t expect, const int32_t update)
{
    // http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
// CMPXCHG r/m32, r32 	Compare EAX with r/m32. If equal, ZF is set and r32 is loaded into r/m32. Else, clear ZF and load r/m32 into AL
//    +---+--------------------------+
//    | r |    Register(s)           |
//    +---+--------------------------+
//    | a |   %eax, %ax, %al         |
//    | b |   %ebx, %bx, %bl         |
//    | c |   %ecx, %cx, %cl         |
//    | d |   %edx, %dx, %dl         |
//    | S |   %esi, %si              |
//    | D |   %edi, %di              |
//    |   |                          |
//    | 0 |   keep in ths same reg.  |
//    | m |   memory                 |
//    | q |   Registers a, b, c or d |
//    +---+--------------------------+

    int32_t prev;
    __asm__ __volatile__
            (
                // load expect into into eax
                // "mov eax, %;"
                // load update into into r/m32
                // "mov r/m32, %;"
                // cmpxchg update, value
                // "cmpxchg r/m32, m32"
                // load eax into prev


                // load eax into prev
                // "mov %, eax

                "lock;" // make cmpxchg atomic
                "cmpxchg %3,%4;" // cmpxchg update, value
                // output operands
                : "=a" (prev), "=m" (value)
                // input operands
                : "a" (expect), "q" (update), "m" (value)
                //: "0" (expect), "q" (update), "m" (value)
             );
    return prev==expect;
}

int32_t AtomicInt32::fetchAndAdd(int32_t increment)
{
    //XADD r/m32, r32 	Exchange r32 and r/m32; load sum into r/m32.
    __asm__ __volatile__ (
                "lock;"
                "xadd %2, %1;"
                :"=a" (increment)
                : "m" (value), "a" (increment)
                :"memory" );
    return increment;
}


const AtomicInt32 AtomicInt32::operator++ ()
{
    AtomicInt32 temp(*this);
    for (;;) {
        int32_t current = get();
        int32_t next = current + 1;
        if (compareAndSet(current, next)) return temp;
    }
}

const AtomicInt32 AtomicInt32::operator++ (int theFlag)
{
    for (;;) {
        int32_t current = get();
        int32_t next = current + 1;
        if (compareAndSet(current, next)) return *this;
    }
}

const AtomicInt32 AtomicInt32::operator-- ()
{
    AtomicInt32 temp(*this);
    for (;;) {
        int32_t current = get();
        int32_t next = current - 1;
        if (compareAndSet(current, next)) return temp;
    }
}

const AtomicInt32 AtomicInt32::operator-- (int theFlag)
{
    AtomicInt32 temp(*this);
    for (;;) {
        int32_t current = get();
        int32_t next = current - 1;
        if (compareAndSet(current, next)) return *this;
    }
}

const int32_t AtomicInt32::operator+= (int32_t increment)
{
    for (;;) {
        int32_t currentValue = get();
        int32_t newValue = currentValue + increment;
        if (compareAndSet(currentValue, newValue))
            return newValue;
    }

}

const bool AtomicInt32::operator== (int32_t comparator)
{
    return value==comparator;
}

int32_t AtomicInt32::getAndAdd(const int32_t increment)
{
    for (;;) {
        int32_t current = get();
        int32_t next = current + increment;
        if (compareAndSet(current, next))
            return current;
    }
}

int32_t AtomicInt32::getAndSet(const int32_t newValue)
{
    for (;;) {
        int32_t current = get();
        if (compareAndSet(current, newValue))
            return current;
    }
}

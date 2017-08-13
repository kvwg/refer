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
#include "atomicInt64.h"

using namespace hba::atomic;

bool AtomicInt64::compareAndSet(int64_t expect, int64_t update)
{
    // CMPXCHG8B m64 	Compare EDX:EAX with m64. If equal, set ZF and load ECX:EBX into m64. Else, clear ZF and load m64 into EDX:EAX.
    // http://faydoc.tripod.com/cpu/cmpxchg8b.htm
    unsigned char casResult;
    __asm__ __volatile__ (
                // load expect into into edx:eax
                // "mov eax, %;"
                // "mov edx, %;"

                // load update into ecx:ebx
                // "mov ebx, %;"
                // "mov ecx, %;"

                "lock;" // make cmpxchg8b atomic
                "cmpxchg8b %2;" // cmpxchg8b destination //sets ZF on success
                "setz %1;" // if ZF set, set casResult to 1

                // output operands
                : "=m" (value), "=q" (casResult)

                // input operands
                : "m" (value), "a" (expect & 0xffffffff), "d" (expect >> 32), "b" (update & 0xffffffff), "c" (update >> 32)

                // list of clobbered registers
                : "cc", "memory");
    return casResult==1;

}

int64_t AtomicInt64::fetchAndAdd(int64_t increment)
{
    //see in arch/x86/include/asm/rwsem.h
    //XADDL r/m64, r64 	Exchange r64 and r/m64; load sum into r/m64.
    __asm__ __volatile__ (
                "lock;" // make xaddl atomic
                "xadd %2, %1;"

                // output operands
                :"=a" (increment)

                // input operands
                :  "m" (value), "d" (increment)

                // list of clobbered registers
                :"memory" );
    return increment;
}

const AtomicInt64 AtomicInt64::operator++ ()
{
    AtomicInt64 temp(value);
    fetchAndAdd(1);
    return temp;
//    for (;;) {
//        int64_t current = get();
//        int64_t next = current + 1;
//        if (compareAndSet(current, next)) return temp;
//    }
}

const AtomicInt64 AtomicInt64::operator++ (int unused)
{
    fetchAndAdd(1);
    return *this;
//    for (;;) {
//        int64_t current = get();
//        int64_t next = current + 1;
//        if (compareAndSet(current, next)) return *this;
//    }
}

const AtomicInt64 AtomicInt64::operator-- ()
{
    AtomicInt64 temp(value);
    fetchAndAdd(-1);
    return temp;
//    for (;;) {
//        int64_t current = get();
//        int64_t next = current - 1;
//        if (compareAndSet(current, next)) return temp;
//    }
}

const AtomicInt64 AtomicInt64::operator-- (int unused)
{
    fetchAndAdd(-1);
    return *this;
//    for (;;) {
//        int64_t current = get();
//        int64_t next = current - 1;
//        if (compareAndSet(current, next)) return *this;
//    }
}

const int64_t AtomicInt64::operator+= (int64_t increment)
{
    for (;;) {
        int64_t currentValue = get();
        int64_t newValue = currentValue + increment;
        if (compareAndSet(currentValue, newValue))
            return newValue;
    }
}

const bool AtomicInt64::operator== (int64_t comparator)
{
    return value==comparator;
}

const bool AtomicInt64::operator== (int comparator)
{
    return value==(int64_t)comparator;
}

int64_t AtomicInt64::addAndGet(const int64_t increment) {
    fetchAndAdd(increment);
    return value;
//    for (;;) {
//        int64_t currentValue = get();
//        int64_t newValue = currentValue + increment;
//        if (compareAndSet(currentValue, newValue))
//            return newValue;
//    }
}

int64_t AtomicInt64::getAndAdd(const int64_t increment)
{
    int64_t ret = value;
    fetchAndAdd(increment);
    return ret;
//    for (;;) {
//        int64_t current = get();
//        int64_t next = current + increment;
//        if (compareAndSet(current, next))
//            return current;
//    }
}

int64_t AtomicInt64::getAndSet(const int64_t newValue)
{
    for (;;) {
        int64_t current = get();
        if (compareAndSet(current, newValue))
            return current;
    }
}

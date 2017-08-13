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
#include "atomicBool.h"

using namespace hba::atomic;

bool AtomicBool::compareAndSet(const bool expect, const bool update)
{
    int8_t e = expect ? 1 : 0;
    int8_t u = update ? 1 : 0;
    int8_t prev;
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
                : "a" (e), "q" (u), "m" (value)
                //: "0" (expect), "q" (update), "m" (value)
             );
    return prev==e;
}

const bool AtomicBool::operator== (bool comparator)
{
    return comparator & (value != 0);
}

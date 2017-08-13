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
#ifndef ATOMICBOOL_H
#define ATOMICBOOL_H

#include <cstdint>

namespace hba {
namespace atomic {

    class AtomicBool
    {
    private:
        int8_t value = 0;
    public:
        AtomicBool() {}
        AtomicBool(const bool initialValue){value = initialValue ? 1 : 0;}
        AtomicBool(const AtomicBool &initialValue) {value = initialValue.value;}

        bool get() {return value != 0;}
        void set(const bool newValue) {value = newValue ? 1 : 0;}

        bool compareAndSet(const bool expect, const bool update);

        const bool operator== (bool comparator);
    };

}
}

#endif // ATOMICBOOL_H

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
#ifndef PADDEDINT64_H
#define PADDEDINT64_H

#include <cstdint>
#include "baseDisruptorClass.h"

namespace disruptor {

    /**
     * @brief
     * Cache line padded int64 variable to be used when false sharing maybe an issue.
     */
    class PaddedInt64 : public BaseDisruptorClass
    {
    private:
        volatile int64_t value = 0;
        //Padding to get the class up to one Cashe Line = 64 bytes
        volatile int64_t p1=1, p2=2, p3=3, p4=4, p5=5, p6=6, p7=7L;

    public:
        PaddedInt64() {}
        PaddedInt64(const int64_t initialValue) {value = initialValue;}

        int64_t get() {return value;}
        void set(const int64_t value) {this->value = value;}

        std::size_t hashCode() const {std::hash<int64_t>hash_fn; return hash_fn(value);}

        //To cheed the compiler to not optimize away my padding
        int64_t sumPaddingToPreventOptimisation() {
            return p1+p2+p3+p4+p5+p6+p7;
        }
    };

}

namespace std {
    template<>
    class hash<disruptor::PaddedInt64> {
    public :
        size_t operator()(const disruptor::PaddedInt64 &paddedInt64 ) const {
            return paddedInt64.hashCode();
        }
    };
}

#endif // PADDEDINT64_H

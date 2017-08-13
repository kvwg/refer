#ifndef ATOMICINT64ARRAY_H
#define ATOMICINT64ARRAY_H

#include <cstdint>
#include "atomicInt64.h"
#include "indexOutOfBoundsException.h"

namespace hba {
namespace atomic {

    class AtomicInt64Array
    {
    private:
        AtomicInt64 *array;
        int arrayLength;

    public:
        AtomicInt64Array(int length);
        ~AtomicInt64Array();

        int length() {return arrayLength;}
        int64_t get(int i) {return array[checkedByteOffset(i)].get();}
        void set(int i, int64_t newValue) {array[checkedByteOffset(i)].set(newValue);}

        AtomicInt64 & operator[] (int i);

    private:
        int checkedByteOffset(int i);

    };

}
}

#endif // ATOMICINT64ARRAY_H

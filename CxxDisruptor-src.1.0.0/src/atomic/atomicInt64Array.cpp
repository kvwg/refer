#include "atomicInt64Array.h"

using namespace hba::atomic;

AtomicInt64Array::AtomicInt64Array(int length)
{
    arrayLength = length;
    array = new AtomicInt64[length];
}

AtomicInt64Array::~AtomicInt64Array()
{
    delete [] array;
}

AtomicInt64 & AtomicInt64Array::operator[] (int i)
{
    return array[checkedByteOffset(i)];
}




int AtomicInt64Array::checkedByteOffset(int i)
{
    if (i < 0 || i >= arrayLength) throw hba::IndexOutOfBoundsException("Too big, or to small (< 0) index was passed: "+i);

    return i;
}

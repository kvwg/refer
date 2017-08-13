#ifndef GATINGSEQUENCEARRAY_H
#define GATINGSEQUENCEARRAY_H

#include <stdarg.h>
#include <utility>
#include "atomicInt64.h"
#include "indexOutOfBoundsException.h"

namespace disruptor {
    class SequenceArray
    {
    private:
        hba::atomic::AtomicInt64 **sequences;
        const int length;

    public:
        SequenceArray(const int size) : length(size) {
            sequences = new hba::atomic::AtomicInt64 *[length];
        }

        SequenceArray(const int numberOfSequences, hba::atomic::AtomicInt64 *sequence, ...) : length(numberOfSequences) {
            sequences = new hba::atomic::AtomicInt64 *[length];
            va_list args;
            va_start(args, sequence);
            hba::atomic::AtomicInt64 *p = sequence;
            int i=0;
            do {
                sequences[i] = p;
                p = va_arg(args,  hba::atomic::AtomicInt64 *);
                i++;
            } while (i<numberOfSequences);
            va_end(args);
        }

    //    SequenceArray(SequenceArray&& oldObject) = delete;
        SequenceArray(SequenceArray&& oldObject): length(oldObject.length) {
            sequences = oldObject.sequences;
            oldObject.sequences = nullptr;
        }


        ~SequenceArray() {
            if (sequences!=nullptr) delete [] sequences;
        }

        int size() {return length;}

        hba::atomic::AtomicInt64& operator[] (int i) {
            if (i>=length) throw hba::IndexOutOfBoundsException();
            return *sequences[i];
        }

        void set(hba::atomic::AtomicInt64* value, int index) {
            if (index>=length) throw hba::IndexOutOfBoundsException();
            sequences[index] = value;
        }

        /**
         * @brief forward
         * @return a new pointer to a SequenceArray there contains all the referenced from this.
         * This references will be nullfied.
         */
        SequenceArray* forward() {
            return new SequenceArray(std::forward<SequenceArray>(*this));
        }
    };
}

#endif // GATINGSEQUENCEARRAY_H

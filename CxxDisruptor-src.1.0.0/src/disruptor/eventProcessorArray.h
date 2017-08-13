#ifndef EVENTPROCESSORARRAY_H
#define EVENTPROCESSORARRAY_H

#include <stdarg.h>
#include "eventProcessor.h"
#include "indexOutOfBoundsException.h"

namespace disruptor {
    class EventProcessorArray : public BaseDisruptorClass
    {
    private:
        EventProcessor **processors;
        const int length;

    public:
        EventProcessorArray(const int size) : length(size) {
            processors = new EventProcessor *[size];
        }

        EventProcessorArray(const int size, EventProcessor *processors[]) : length(size) {
            this->processors = new EventProcessor *[size];
            for (int i=0; i<size; i++) this->processors[i] =processors[i];
        }

        EventProcessorArray(const int numberOfProcessors, EventProcessor *processor, ...) : length(numberOfProcessors) {
            processors = new EventProcessor *[numberOfProcessors];
            va_list args;
            va_start(args, processor);
            EventProcessor *p = processor;
            int i=0;
            do {
                processors[i] = p;
                p = va_arg(args, EventProcessor *);
                i++;
            } while (i<numberOfProcessors);
            va_end(args);
        }

        EventProcessorArray(EventProcessorArray&& oldObject): length(oldObject.length) {
            processors = oldObject.processors;
            oldObject.processors = nullptr;
        }


        ~EventProcessorArray() {
            if (processors!=nullptr) delete [] processors;
        }

        int size() {return length;}


        EventProcessor& operator[] (int i) {
            if (i>=length) throw hba::IndexOutOfBoundsException();
            return *processors[i];
        }

        void set(EventProcessor* value, int index) {
            if (index>=length) throw hba::IndexOutOfBoundsException();
            processors[index] = value;
        }

    };
}

#endif // EVENTPROCESSORARRAY_H

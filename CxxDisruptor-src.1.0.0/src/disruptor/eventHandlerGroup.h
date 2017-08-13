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
#ifndef EVENTHANDLERGROUP_H
#define EVENTHANDLERGROUP_H

#include "disruptor.h"
#include "eventProcessorRepository.h"
#include "eventProcessor.h"
#include "util.h"

namespace disruptor {

    template <class T> class Disruptor;

    /**
     * @brief
     * A group of {@link EventProcessor}s used as part of the {@link Disruptor}.
     *
     * @param <T> the type of entry used by the event processors.
     */
    template <class T>
    class EventHandlerGroup : public BaseDisruptorClass
    {
    private:
        Disruptor<T> *disruptor;
        EventProcessorRepository<T> *eventProcessorRepository;
        EventProcessorArray *eventProcessors;

    public:
        /**
         * @brief EventHandlerGroup
         * @param disruptor
         * @param eventProcessorRepository
         * @param eventProcessors
         * @param eventProcessorsLength
         */
        EventHandlerGroup(Disruptor<T> *disruptor, \
                          EventProcessorRepository<T> *eventProcessorRepository, \
                          EventProcessorArray &eventProcessors)
        {
            this->disruptor = disruptor;
            this->eventProcessorRepository = eventProcessorRepository;

            this->eventProcessors = &eventProcessors;
        }

        ~EventHandlerGroup()
        {
//            delete eventProcessors;
        }



        /**
         * @brief and
         * Create a new event handler group that combines the handlers in this group with
         * handlers.
         *
         * @param numberOfHandlers number of event handlers
         * @param handler one or more event handlers
         * @return this EventHandlerGroup combining the existing and new handlers into a
         * single dependency group.
         */
        EventHandlerGroup<T>* _and(const int numberOfHandlers, const EventHandler<T> *handler, ...)
        {
            EventProcessorArray *combinedProcessors = new EventProcessorArray(eventProcessors->size()+numberOfHandlers);
            va_list args;
            va_start(args, handler);
            combinedProcessors->set(handler, 0);//TODO: This is the original code but has no sence: How is the handler ended in the repository at this point?
            for (int i=1; i<numberOfHandlers; i++) {
                combinedProcessors->set(eventProcessorRepository->getEventProcessorFor( *va_arg(args, EventHandler<T>  *)), i); //TODO: Same as above
            }
            va_end(args);

            for (int i=0; i<eventProcessors->size(); i++) {
                combinedProcessors->set((EventProcessor *)&eventProcessors[i], numberOfHandlers+i);
            }

            delete eventProcessors;
            eventProcessors = combinedProcessors;
            return this;
            //return new EventHandlerGroup<T>(disruptor, eventProcessorRepository, combinedProcessors);
        }


        /**
         * @brief and
         * Create a new event handler group that combines the handlers in this group with processors.
         *
         * @param numberOfProcessors number of evet Procesors.
         * @param processor one or more event processor the will precess events.
         * @return this EventHandlerGroup combining the existing and new processors into a single dependency group.
         */
        EventHandlerGroup<T>* _and(const int numberOfProcessors, EventProcessor *processor, ...)
        {
            EventProcessorArray *combinedProcessors = new EventProcessorArray(eventProcessors->size()+numberOfProcessors);
            va_list args;
            va_start(args, processor);

            eventProcessorRepository->add(processor);
            combinedProcessors->set(processor, 0);
            for (int i=1; i<numberOfProcessors; i++) {
                EventProcessor *p = va_arg(args, EventProcessor *);
                eventProcessorRepository->add(p);
                combinedProcessors->set(p, i);
            }
            va_end(args);

            for (int i=0; i<eventProcessors->size(); i++) {
                combinedProcessors->set((EventProcessor *)&eventProcessors[i], i+numberOfProcessors);
            }

            delete eventProcessors;
            eventProcessors = combinedProcessors;
            return this;
        }


        /**
         * @brief then
         * Set up batch handlers to consume events from the ring buffer. These handlers will only process events
         * after every EventProcessor in this group has processed the event.
         *
         * <p>This method is generally used as part of a chain. For example if the handler <code>A</code> must
         * process events before handler <code>B</code>:</p>
         *
         * <pre><code>
         * dw.handleEventsWith(A, 1)->then(B, 1);
         * </code></pre>
         *
         * @param numberOfHandlers number of event handlers
         * @param handler one or more event handlers
         * @return a EventHandlerGroup that can be used to set up a event processor barrier over the created event processors.
         */
        EventHandlerGroup<T>* then(int numberOfHandlers , EventHandler<T> *handler, ...)
        {
            va_list args;
            va_start(args, handler);
            EventHandler<T> *p = handler;
            EventHandlerGroup<T>* group = disruptor->createEventProcessors(*eventProcessors, numberOfHandlers, p, args);
            va_end(args);
            return group;
        }

        /**
         * @brief handleEventsWith
         * Set up batch handlers to handleEventException events from the ring buffer. These handlers will only process events
         * after every EventProcessor in this group has processed the event.
         *
         * <p>This method is generally used as part of a chain. For example if the handler A must
         * process events before handler B:</p>
         *
         * <pre><code>
         * dw.after(A, 1)->handleEventsWith(B, 1);
         * </code></pre>
         *
         * @param numberOfHandlers number of event handlers
         * @param handler one or more event handlers
         * @return a EventHandlerGroup that can be used to set up a event processor barrier over the created event processors.
         */
        EventHandlerGroup<T>* handleEventsWith(int numberOfHandlers , EventHandler<T> *handler, ...)
        {
            va_list args;
            va_start(args, handler);
            EventHandler<T> *p = handler;
            EventHandlerGroup<T>* group = disruptor->createEventProcessors(*eventProcessors, numberOfHandlers, p, args);
            va_end(args);
            return group;
        }

        /**
         * @brief asSequenceBarrier
         * Create a dependency barrier for the processors in this group.
         * This allows custom event processors to have dependencies on
         * BatchEventProcessors created by the disruptor.
         *
         * @return a SequenceBarrie} including all the processors in this group.
         */
        SequenceBarrier* asSequenceBarrier()
        {
            return disruptor->getRingBuffer()->newBarrier(Util::getSequencesFor(*eventProcessors));
        }
    };
}

#endif // EVENTHANDLERGROUP_H

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
#ifndef GARBAGELIST_H
#define GARBAGELIST_H

#include "baseDisruptorClass.h"

namespace disruptor {

    class GarbageDeleter
    {
    public:
        virtual void deleteObject(BaseDisruptorClass *object) = 0;
    };

    class GarbageArrayDeleter : public GarbageDeleter
    {
        void deleteObject(BaseDisruptorClass *object)
        {
            delete [] object;
        }
    };

    class GarbageHolder
    {
    public:
        GarbageHolder *next;
        BaseDisruptorClass *garbagePtr;
        BaseDisruptorClass **garbagePtrPtr;

        GarbageHolder(BaseDisruptorClass *garbageToCollect)
        {
            next = nullptr;
            garbagePtr = garbageToCollect;
            garbagePtrPtr = nullptr;
        }

        GarbageHolder(BaseDisruptorClass **garbageToCollect)
        {
            next = nullptr;
            garbagePtr = nullptr;
            garbagePtrPtr = garbageToCollect;
        }

        ~GarbageHolder()
        {
            if (garbagePtr != nullptr) delete [] garbagePtr;
            if (garbagePtrPtr != nullptr) delete [] garbagePtrPtr;
        }
    };

    class GarbageList
    {
    private:
        GarbageHolder *first, *last;

    public:
        GarbageList()
        {
            first = last = nullptr;
        }

        ~GarbageList()
        {
            GarbageHolder *ptr = first;
            while (ptr != nullptr) {
                GarbageHolder *ack = ptr;
                ptr =  ptr->next;
                delete ack;
            }
        }

        void add(BaseDisruptorClass *garbageToCollect)
        {
            GarbageHolder *holder = new GarbageHolder(garbageToCollect);
            if (first==nullptr) {
                first = last = holder;
            }
            else {
                last->next = holder;
                last = holder;
            }
        }

        void add(BaseDisruptorClass **garbageToCollect)
        {
            GarbageHolder *holder = new GarbageHolder(garbageToCollect);
            if (first==nullptr) {
                first = last = holder;
            }
            else {
                last->next = holder;
                last = holder;
            }
        }

    };

}

#endif // GARBAGELIST_H

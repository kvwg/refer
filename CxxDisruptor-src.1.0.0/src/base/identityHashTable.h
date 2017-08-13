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
#ifndef IDENTITYHASHTABLE_H
#define IDENTITYHASHTABLE_H

#include <functional>
#include "illegalArgumentException.h"

namespace hba {
    /*
     * This class implements a hash table, using
     * reference-equality in place of object-equality when comparing keys (and
     * values).  In other words, in an IdentityHashTable, two keys
     * k1 and k2 are considered equal if and only if
     * (k1==k2).  (In normal Hash Map implementations
     * two keys k1 and k2 are considered equal
     * if and only if (k1==null ? k2==null : k1.equals(k2)).)
     *
     */
    template <class T>
    class IdentityHashTable
    {
    private:
        template <class E>
        class Item
        {
        public:
            Item(){}
            int key = hba::IdentityHashTable<T>::KEY_NULL;
            E *value = nullptr;
        };


        static const int KEY_NULL = 0;
        static const int  KEY_DELETED = 1;
        const float HASH_TABLE_MAX_FULL = 0.65f;
        const float HASH_TABLE_EMPTY = 0.3f;
        const float HASH_DELETE_REHASH = 0.8f;

        Item<T> *items;

        std::hash<T> hashFunction;
        int indexMask;
        bool hasKey[2];
        Item<T> value[2]; // handle out of bound values
        int length;
        int population;
        int deletes;
        int growSize;
        int shrinkSize;
        int deleteSize;
        int rehashes = 0;

        int valueCountIterator;
        int itemCountIterator;


    public:
        IdentityHashTable() {
//            create(0x100); //TODO: find a good start value
            create(8);
         }
        IdentityHashTable(const int size)
        {
            create(size);
        }
        ~IdentityHashTable() {deleteItems(items, length);}

        Item<T>* getItems() {return items;}

        int getKey(T &obj)
        {
            int key = (int)hashFunction(obj);
            if (get(key)!=nullptr) return key;
            return KEY_NULL;
        }

        T* get(int key)
        {
//            if (key <= KEY_DELETED) {
//                if (hasKey[key]) return value[key].value;
//                return nullptr;
//            }

            Item<T> *item = findHash(key);
            if (item == nullptr) return nullptr;
            return item->value;
        }

        int set(T &value)
        {
            int key = (int)hashFunction(value);
            return hashInsert(*this, key, value);
        }

        T* set(int key, T &value)
        {
            T *oldVal = get(key);
            hashInsert(*this, key, value);
            return oldVal;
        }

        T* remove(int key)
        {
            Item<T> *item = findHash(key);
            if (item==nullptr) return nullptr;

            if (0<=key && key <= KEY_DELETED) {
                hasKey[key] = false;
            }

            item->key = KEY_DELETED;
            T* value = item->value;
            population--;
            deletes++;
            if (population < shrinkSize) {
                rehash(length >> 1);
            }
            else if (population + deletes >= deleteSize) {
                rehash(length);
            }

            return value;
        }

        T* iteratorFirst()
        {
            valueCountIterator = 0;
            itemCountIterator = 0;
            return iteratorNext();
        }

        T* iteratorNext()
        {
            for (; valueCountIterator<2; valueCountIterator++) {
                if (hasKey[valueCountIterator]) return value[valueCountIterator++].value;
            }

            for (; itemCountIterator<length; itemCountIterator++) {
                if (items[itemCountIterator].key > KEY_DELETED || items[itemCountIterator].key < 0) return items[itemCountIterator++].value;
            }
            return nullptr;

        }

        /*
         *TODO: getValues is depricated as it does not fubnction correctly
         */
        T** getValues()
        {
            T **vals = new T*[population+1]; //TODO: memory-leak? Who delete vals?
            T *val = *vals;
            int inx=0;
            for (int i=0; i<2; i++) {
                if (hasKey[i]) {
                    val = vals[inx];
                    vals[inx++] = value[i].value;
//                    val = value[i].value;
//                    val++;
//                    inx++;
                }
            }

            for (int i=0; i<length && inx<population; i++) {
                Item<T> it = items[i];
                T *v = items[i].value;
                if (items[i].key>KEY_DELETED || items[i].key<0) {
                    val = vals[inx];
                    vals[inx++] = items[i].value;
//                    val = items[i].value;
//                    val++;
//                    inx++;
                }
            }
            vals[inx] = nullptr;

            for (int i=0; i<population+1; i++) {
                T *t = vals[i];
            }

            return vals;
        }

        int getRehashes() {return rehashes;}

        int getLength() {return length;}

        int getPopulation() {return population;}


    private:
        void create(const int size)
        {
            if (size < 8) length = 8;
            else length = size;
            if (bitCount(length) != 1) throw IllegalArgumentException("bufferSize must be a power of 2");
            indexMask = length - 1;
            population = deletes = 0;
            hasKey[0] = hasKey[1] = false;
            growSize = (int)(length * HASH_TABLE_MAX_FULL) - 1;
            if (growSize < 2) growSize = 2;
            shrinkSize = (int)(length * HASH_TABLE_EMPTY);
            if (length == 8) shrinkSize = 0;
            deleteSize = (int)(length * HASH_DELETE_REHASH) - 1;
            items = new Item<T>[length];
            for (int i=0; i<length; i++) {
                items[i].key = KEY_NULL;
                items[i].value = nullptr;
            }
        }

        void deleteItems(Item<T> itemsToDel[], const int itemsToDelLength)
        {
//            for (int i=0; i<itemsToDelLength; i++) {
//                itemsToDel[i].value = nullptr;
//            }
            delete [] itemsToDel;
        }

        Item<T>* findHash(int key)
        {
            int hash = hashWord(key);
            int p = hash & indexMask;
            if (0<=key && key <= KEY_DELETED) {
                if (hasKey[key]) return &value[key];
                return nullptr;
            }

            if (items[p].key == key) return &items[p];
            if (items[p].key == KEY_NULL) return nullptr;

            int s = (((hash >> 16) | (hash << 16)) & indexMask) | 1;
            //assert(d->population + d->deletes != d->data_len);
            do {
                p = (p + s) & indexMask;
                if (items[p].key == key) return &items[p];
            } while (items[p].key != KEY_NULL);

            return nullptr;
        }

        int hashInsert(IdentityHashTable<T> &table, int key, T &value)
        {
            int f = -1;
            int hash = hashWord(key);
            int p = hash & table.indexMask;

            if (0 <= key && key <= KEY_DELETED) {
                if (!table.hasKey[key])table.population++;
                table.hasKey[key] = true;
                table.value[key].key = key;
                table.value[key].value = &value;
                return key;
            }

            if (table.items[p].key == key) {
                table.items[p].value = &value;
                return key;
            }

            if (table.items[p].key == KEY_DELETED) f = p;
            if (table.items[p].key > KEY_NULL) { // Cell occupied
                int s = (((hash >> 16) | (hash << 16)) & table.indexMask) | 1;
                //assert(d->population + d->deletes != d->data_len);
                do {
                    p = (p + s) & table.indexMask;
                    if (table.items[p].key == key) {
                        table.items[p].value = &value;
                        return key;
                    }
                    if (table.items[p].key == KEY_DELETED && f == -1) f = p;
                } while (table.items[p].key > KEY_NULL);
            }

            if (table.items[p].key == KEY_NULL && table.population >= table.growSize) {
                rehash(table.length * 2);
                return hashInsert(table, key, value);
            }
            else if (table.population + table.deletes > table.deleteSize) {
                rehash(table.length);
                return hashInsert(table, key, value);
            }
            else {
                if (f >= 0) p = f;
                if (table.items[p].key == KEY_DELETED) table.deletes--;
                table.items[p].key = key;
                table.items[p].value = &value;
                table.population++;
                return key;
            }
        }

        void rehash(int len)
        {
            rehashes++;

            Item<T> *oldItems = items;
            int oldItemsLenghth = length;

            bool oldHasKey[2];
            Item<T> oldValue[2];
            for (int i=0; i<2; i++) {
                oldHasKey[i] = hasKey[i];
                oldValue[i].key = value[i].key;
                oldValue[i].value = value[i].value;
            }


            create(len);

            for (int i=0; i<oldItemsLenghth; i++) {
                if (oldItems[i].key > KEY_DELETED) {
                    int p = hashInsert(*this, oldItems[i].key, *oldItems[i].value);
                }
            }

            for (int i=0; i<2; i++) {
                if (oldHasKey[i]) {
                    hashInsert(*this, oldValue[i].key, *oldValue[i].value);
                }
            }

            deleteItems(oldItems, oldItemsLenghth);


//            IdentityHashTable<T> newTable(len);

//            for (int i=0; i < length; ++i) {
//                if (items[i].key > KEY_DELETED) {
//                    int p = hashInsert(newTable, items[i].key, *items[i].value);
//        //            assert(p != KEY_NULL);
//                }
//            }
////            assert(newTable.population == population);
//            copy(newTable);
        }

        void copy(IdentityHashTable<T> &tab)
        {
            Item<T> *oldItems = this->items;
            int oldItemsLength = this->length;

            this->length = tab.length;
            this->items = tab.items;
        //		this.hasKey[0] = tab.hasKey[0]; this.value[0] = tab.value[0];
        //		this.hasKey[1] = tab.hasKey[1]; this.value[1] = tab.value[1];
            this->indexMask = tab.indexMask;
            this->population = tab.population;
            this->deletes = tab.deletes;
            this->growSize = tab.growSize;
            this->shrinkSize = tab.shrinkSize;
            this->deleteSize = tab.deleteSize;

            deleteItems(oldItems, oldItemsLength);
        }

        int hashWord(int key)
        {
            // Bob Jenkin's mix function, possibly overkill for only 32 bits?
            // but a simpler one was no faster, so what the heck
            int a, b, c;
            a = b = 0x9e3779b9;  // the golden ratio; an arbitrary value
            c = key;
            a -= b; a -= c; a ^= (c>>13);
            b -= c; b -= a; b ^= (a<<8);
            c -= a; c -= b; c ^= (b>>13);
            a -= b; a -= c; a ^= (c>>12);
            b -= c; b -= a; b ^= (a<<16);
            c -= a; c -= b; c ^= (b>>5);
            a -= b; a -= c; a ^= (c>>3);
            b -= c; b -= a; b ^= (a<<10);
            c -= a; c -= b; c ^= (b>>15);
            return c;
        }

        /**
         * Returns the number of one-bits in the two's complement binary
         * representation of the specified int value.  This function is
         * sometimes referred to as the population count.
         *
         * @return the number of one-bits in the two's complement binary
         *     representation of the specified {@code int} value.
         */
        int bitCount(int i)
        {
            // HD, Figure 5-2
            i = i - ((i >> 1) & 0x55555555);
            i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
            i = (i + (i >> 4)) & 0x0f0f0f0f;
            i = i + (i >> 8);
            i = i + (i >> 16);
            return i & 0x3f;

        }

    };

}

#endif // IDENTITYHASHTABLE_H

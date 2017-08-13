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
#ifndef IDENTITYHASHMAP_H
#define IDENTITYHASHMAP_H

#include "identityHashTable.h"

namespace hba {

    template <class K, class V>
    class IdentityHashMap
    {
    private:
        IdentityHashTable<V> table;
        std::hash<K> hashFunction;

    public:
        IdentityHashMap()
        {
        }

        IdentityHashMap(const int size) : table(size)
        {
        }

        V* get(const K &key)
        {
            int k = hashFunction(key);
            return table.get(k);
        }

        V* put(const K &key, V &value)
        {
            int k = hashFunction(key);
            return table.set(k, value);
         }

        V* remove(const K &key)
        {
            int k = hashFunction(key);
            return table.remove(k);
        }

        V* iteratorFirst()
        {
            return table.iteratorFirst();
        }

        V* iteratorNext()
        {
            return table.iteratorNext();
        }

        V** values() {
            table.getValues();
        }

        int getPopulation()
        {
            return table.getPopulation();
        }
    };

}

#endif // IDENTITYHASHMAP_H

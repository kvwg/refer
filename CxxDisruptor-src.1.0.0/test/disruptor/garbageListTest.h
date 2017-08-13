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
#ifndef GARBAGELISTTEST_H
#define GARBAGELISTTEST_H

#include <cxxtest/TestSuite.h>
#include <typeinfo>
#include "garbageList.h"

int templateDeleteCount = 0;
int classDeleteCount = 0;

template <class T>
class TestTemplate : public disruptor::BaseDisruptorClass
{
private:
    //T *value;
    T val;

public:
    TestTemplate()
    {
        //value = new T();
    }

    ~TestTemplate()
    {
        //delete value;
        templateDeleteCount++;
    }
};

class TestClass
{
private:


public:
    TestClass()
    {
    }

    ~TestClass()
    {
        classDeleteCount++;
    }
};

class GarbageListTest : public CxxTest::TestSuite
{
public:
    void setUp()
    {
        templateDeleteCount = 0;
        classDeleteCount = 0;
    }

    void testList(void)
    {
        disruptor::GarbageList *garbage = new disruptor::GarbageList();

        TestTemplate<TestClass> *simpleTemplate = new TestTemplate<TestClass>();
        disruptor::BaseDisruptorClass *baseClass1 = dynamic_cast<disruptor::BaseDisruptorClass *>(simpleTemplate);
        TS_ASSERT(baseClass1 != nullptr);
        garbage->add(simpleTemplate);

        TestTemplate<TestClass> *array = new TestTemplate<TestClass>[10];
//        disruptor::BaseDisruptorClass *baseClass2 = dynamic_cast<disruptor::BaseDisruptorClass []>(simpleTemplate);
//        garbage->add(array);

        TestTemplate<TestClass> **ptrArray = new TestTemplate<TestClass>*[10];
        garbage->add((disruptor::BaseDisruptorClass**)ptrArray);

        delete garbage;


        CXXTEST_STD(cout) << "Deleted " << templateDeleteCount << " templates." << CXXTEST_STD(endl);
        CXXTEST_STD(cout) << "Deleted " << classDeleteCount << " classes." << CXXTEST_STD(endl);
    }
};

#endif // GARBAGELISTTEST_H

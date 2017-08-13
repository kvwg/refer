/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    status = CxxTest::Main<CxxTest::ErrorPrinter>( tmp, argc, argv );
    return status;
}
bool suite_GarbageListTest_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/garbageListTest.h"

static GarbageListTest suite_GarbageListTest;

static CxxTest::List Tests_GarbageListTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GarbageListTest( "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/garbageListTest.h", 62, "GarbageListTest", suite_GarbageListTest, Tests_GarbageListTest );

static class TestDescription_suite_GarbageListTest_testList : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GarbageListTest_testList() : CxxTest::RealTestDescription( Tests_GarbageListTest, suiteDescription_GarbageListTest, 71, "testList" ) {}
 void runTest() { suite_GarbageListTest.testList(); }
} testDescription_suite_GarbageListTest_testList;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

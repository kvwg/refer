/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
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
bool suite_IdentityHashTableTest_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/base/identityHashTableTest.h"

static IdentityHashTableTest suite_IdentityHashTableTest;

static CxxTest::List Tests_IdentityHashTableTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_IdentityHashTableTest( "/home/baastruph/projects/CxxDisruptor/trunk/test/base/identityHashTableTest.h", 48, "IdentityHashTableTest", suite_IdentityHashTableTest, Tests_IdentityHashTableTest );

static class TestDescription_suite_IdentityHashTableTest_testAutoResizing : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_IdentityHashTableTest_testAutoResizing() : CxxTest::RealTestDescription( Tests_IdentityHashTableTest, suiteDescription_IdentityHashTableTest, 51, "testAutoResizing" ) {}
 void runTest() { suite_IdentityHashTableTest.testAutoResizing(); }
} testDescription_suite_IdentityHashTableTest_testAutoResizing;

static class TestDescription_suite_IdentityHashTableTest_testIterator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_IdentityHashTableTest_testIterator() : CxxTest::RealTestDescription( Tests_IdentityHashTableTest, suiteDescription_IdentityHashTableTest, 74, "testIterator" ) {}
 void runTest() { suite_IdentityHashTableTest.testIterator(); }
} testDescription_suite_IdentityHashTableTest_testIterator;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

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
bool suite_AtomicInt64ArrayTest_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt64ArrayTest.h"

static AtomicInt64ArrayTest suite_AtomicInt64ArrayTest;

static CxxTest::List Tests_AtomicInt64ArrayTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AtomicInt64ArrayTest( "/home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt64ArrayTest.h", 18, "AtomicInt64ArrayTest", suite_AtomicInt64ArrayTest, Tests_AtomicInt64ArrayTest );

static class TestDescription_suite_AtomicInt64ArrayTest_testSimple : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AtomicInt64ArrayTest_testSimple() : CxxTest::RealTestDescription( Tests_AtomicInt64ArrayTest, suiteDescription_AtomicInt64ArrayTest, 21, "testSimple" ) {}
 void runTest() { suite_AtomicInt64ArrayTest.testSimple(); }
} testDescription_suite_AtomicInt64ArrayTest_testSimple;

static class TestDescription_suite_AtomicInt64ArrayTest_testOperators : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AtomicInt64ArrayTest_testOperators() : CxxTest::RealTestDescription( Tests_AtomicInt64ArrayTest, suiteDescription_AtomicInt64ArrayTest, 35, "testOperators" ) {}
 void runTest() { suite_AtomicInt64ArrayTest.testOperators(); }
} testDescription_suite_AtomicInt64ArrayTest_testOperators;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

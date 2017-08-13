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
bool suite_IdentityHashMapTest_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/base/identityHashMapTest.h"

static IdentityHashMapTest suite_IdentityHashMapTest;

static CxxTest::List Tests_IdentityHashMapTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_IdentityHashMapTest( "/home/baastruph/projects/CxxDisruptor/trunk/test/base/identityHashMapTest.h", 30, "IdentityHashMapTest", suite_IdentityHashMapTest, Tests_IdentityHashMapTest );

static class TestDescription_suite_IdentityHashMapTest_testX : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_IdentityHashMapTest_testX() : CxxTest::RealTestDescription( Tests_IdentityHashMapTest, suiteDescription_IdentityHashMapTest, 33, "testX" ) {}
 void runTest() { suite_IdentityHashMapTest.testX(); }
} testDescription_suite_IdentityHashMapTest_testX;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

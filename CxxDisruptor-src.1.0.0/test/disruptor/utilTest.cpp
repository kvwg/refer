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
bool suite_utilTest_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/utilTest.h"

static utilTest suite_utilTest;

static CxxTest::List Tests_utilTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_utilTest( "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/utilTest.h", 30, "utilTest", suite_utilTest, Tests_utilTest );

static class TestDescription_suite_utilTest_testAffinity : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_utilTest_testAffinity() : CxxTest::RealTestDescription( Tests_utilTest, suiteDescription_utilTest, 33, "testAffinity" ) {}
 void runTest() { suite_utilTest.testAffinity(); }
} testDescription_suite_utilTest_testAffinity;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

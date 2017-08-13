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
bool suite_DisruptorTest_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/disruptorTest.h"

static DisruptorTest suite_DisruptorTest;

static CxxTest::List Tests_DisruptorTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DisruptorTest( "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/disruptorTest.h", 74, "DisruptorTest", suite_DisruptorTest, Tests_DisruptorTest );

static class TestDescription_suite_DisruptorTest_testDisrupter : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DisruptorTest_testDisrupter() : CxxTest::RealTestDescription( Tests_DisruptorTest, suiteDescription_DisruptorTest, 77, "testDisrupter" ) {}
 void runTest() { suite_DisruptorTest.testDisrupter(); }
} testDescription_suite_DisruptorTest_testDisrupter;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

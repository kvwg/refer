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
bool suite_BatchEventProcessorTest_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/batchEventProcessorTest.h"

static BatchEventProcessorTest suite_BatchEventProcessorTest;

static CxxTest::List Tests_BatchEventProcessorTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BatchEventProcessorTest( "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/batchEventProcessorTest.h", 98, "BatchEventProcessorTest", suite_BatchEventProcessorTest, Tests_BatchEventProcessorTest );

static class TestDescription_suite_BatchEventProcessorTest_testHash : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BatchEventProcessorTest_testHash() : CxxTest::RealTestDescription( Tests_BatchEventProcessorTest, suiteDescription_BatchEventProcessorTest, 133, "testHash" ) {}
 void runTest() { suite_BatchEventProcessorTest.testHash(); }
} testDescription_suite_BatchEventProcessorTest_testHash;

static class TestDescription_suite_BatchEventProcessorTest_testStartHalt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BatchEventProcessorTest_testStartHalt() : CxxTest::RealTestDescription( Tests_BatchEventProcessorTest, suiteDescription_BatchEventProcessorTest, 143, "testStartHalt" ) {}
 void runTest() { suite_BatchEventProcessorTest.testStartHalt(); }
} testDescription_suite_BatchEventProcessorTest_testStartHalt;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

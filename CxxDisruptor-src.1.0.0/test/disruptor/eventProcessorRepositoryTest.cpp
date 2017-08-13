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
bool suite_EventProcessorRepositoryTest_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/eventProcessorRepositoryTest.h"

static EventProcessorRepositoryTest suite_EventProcessorRepositoryTest;

static CxxTest::List Tests_EventProcessorRepositoryTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EventProcessorRepositoryTest( "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/eventProcessorRepositoryTest.h", 94, "EventProcessorRepositoryTest", suite_EventProcessorRepositoryTest, Tests_EventProcessorRepositoryTest );

static class TestDescription_suite_EventProcessorRepositoryTest_testAdd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_EventProcessorRepositoryTest_testAdd() : CxxTest::RealTestDescription( Tests_EventProcessorRepositoryTest, suiteDescription_EventProcessorRepositoryTest, 97, "testAdd" ) {}
 void runTest() { suite_EventProcessorRepositoryTest.testAdd(); }
} testDescription_suite_EventProcessorRepositoryTest_testAdd;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

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
bool suite_SequenceTest_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/sequencerTest.h"

static SequenceTest suite_SequenceTest;

static CxxTest::List Tests_SequenceTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SequenceTest( "/home/baastruph/projects/CxxDisruptor/trunk/test/disruptor/sequencerTest.h", 39, "SequenceTest", suite_SequenceTest, Tests_SequenceTest );

static class TestDescription_suite_SequenceTest_testNext : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SequenceTest_testNext() : CxxTest::RealTestDescription( Tests_SequenceTest, suiteDescription_SequenceTest, 57, "testNext" ) {}
 void runTest() { suite_SequenceTest.testNext(); }
} testDescription_suite_SequenceTest_testNext;

static class TestDescription_suite_SequenceTest_testTryNext : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SequenceTest_testTryNext() : CxxTest::RealTestDescription( Tests_SequenceTest, suiteDescription_SequenceTest, 76, "testTryNext" ) {}
 void runTest() { suite_SequenceTest.testTryNext(); }
} testDescription_suite_SequenceTest_testTryNext;

static class TestDescription_suite_SequenceTest_testNewBarrier : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SequenceTest_testNewBarrier() : CxxTest::RealTestDescription( Tests_SequenceTest, suiteDescription_SequenceTest, 96, "testNewBarrier" ) {}
 void runTest() { suite_SequenceTest.testNewBarrier(); }
} testDescription_suite_SequenceTest_testNewBarrier;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

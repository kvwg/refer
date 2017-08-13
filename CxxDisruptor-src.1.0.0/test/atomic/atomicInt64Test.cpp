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
bool suite_AtomicInt64Test_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt64Test.h"

static AtomicInt64Test suite_AtomicInt64Test;

static CxxTest::List Tests_AtomicInt64Test = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AtomicInt64Test( "/home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt64Test.h", 54, "AtomicInt64Test", suite_AtomicInt64Test, Tests_AtomicInt64Test );

static class TestDescription_suite_AtomicInt64Test_testCompareAndSet : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AtomicInt64Test_testCompareAndSet() : CxxTest::RealTestDescription( Tests_AtomicInt64Test, suiteDescription_AtomicInt64Test, 57, "testCompareAndSet" ) {}
 void runTest() { suite_AtomicInt64Test.testCompareAndSet(); }
} testDescription_suite_AtomicInt64Test_testCompareAndSet;

static class TestDescription_suite_AtomicInt64Test_testFetchAndAdd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AtomicInt64Test_testFetchAndAdd() : CxxTest::RealTestDescription( Tests_AtomicInt64Test, suiteDescription_AtomicInt64Test, 71, "testFetchAndAdd" ) {}
 void runTest() { suite_AtomicInt64Test.testFetchAndAdd(); }
} testDescription_suite_AtomicInt64Test_testFetchAndAdd;

static class TestDescription_suite_AtomicInt64Test_testOfArithmetic : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AtomicInt64Test_testOfArithmetic() : CxxTest::RealTestDescription( Tests_AtomicInt64Test, suiteDescription_AtomicInt64Test, 91, "testOfArithmetic" ) {}
 void runTest() { suite_AtomicInt64Test.testOfArithmetic(); }
} testDescription_suite_AtomicInt64Test_testOfArithmetic;

static class TestDescription_suite_AtomicInt64Test_testThreading : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AtomicInt64Test_testThreading() : CxxTest::RealTestDescription( Tests_AtomicInt64Test, suiteDescription_AtomicInt64Test, 108, "testThreading" ) {}
 void runTest() { suite_AtomicInt64Test.testThreading(); }
} testDescription_suite_AtomicInt64Test_testThreading;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

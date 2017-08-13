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
bool suite_AtomicInt32Test_init = false;
#include "/home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt32Test.h"

static AtomicInt32Test suite_AtomicInt32Test;

static CxxTest::List Tests_AtomicInt32Test = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AtomicInt32Test( "/home/baastruph/projects/CxxDisruptor/trunk/test/atomic/atomicInt32Test.h", 29, "AtomicInt32Test", suite_AtomicInt32Test, Tests_AtomicInt32Test );

static class TestDescription_suite_AtomicInt32Test_testCompareAndSet : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AtomicInt32Test_testCompareAndSet() : CxxTest::RealTestDescription( Tests_AtomicInt32Test, suiteDescription_AtomicInt32Test, 32, "testCompareAndSet" ) {}
 void runTest() { suite_AtomicInt32Test.testCompareAndSet(); }
} testDescription_suite_AtomicInt32Test_testCompareAndSet;

static class TestDescription_suite_AtomicInt32Test_testFetchAndAdd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AtomicInt32Test_testFetchAndAdd() : CxxTest::RealTestDescription( Tests_AtomicInt32Test, suiteDescription_AtomicInt32Test, 39, "testFetchAndAdd" ) {}
 void runTest() { suite_AtomicInt32Test.testFetchAndAdd(); }
} testDescription_suite_AtomicInt32Test_testFetchAndAdd;

static class TestDescription_suite_AtomicInt32Test_testOfArithmetic : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AtomicInt32Test_testOfArithmetic() : CxxTest::RealTestDescription( Tests_AtomicInt32Test, suiteDescription_AtomicInt32Test, 51, "testOfArithmetic" ) {}
 void runTest() { suite_AtomicInt32Test.testOfArithmetic(); }
} testDescription_suite_AtomicInt32Test_testOfArithmetic;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";

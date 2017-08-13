cmake_minimum_required(VERSION 2.8)

# Prevent warnings for full path libraries link
cmake_policy(SET CMP0003 NEW)

# We want to use Python not perl!
set(CXXTEST_USE_PYTHON TRUE)

find_package(CxxTest)

if (CXXTEST_FOUND)
        include_directories(../atomic)

        # list all the headers files generating tests
        SET (TEST_NAMES
                sequencerTest
                eventProcessorRepositoryTest
                batchEventProcessorTest
                garbageListTest
                disruptorTest
                utilTest
        )

        ################### COMPILER    ###############################################
        include_directories(${CXXTEST_INCLUDE_DIR})
        #include_directories(. ../src)


        enable_testing()

        foreach(NAME ${TEST_NAMES})

            CXXTEST_ADD_TEST(${NAME} ${NAME}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${NAME}.h)

            # Link our test to our project library
            target_link_libraries(${NAME} ${PROJECT_NAME})

            if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
                add_definitions(-DVQMON_HOST_PLATFORM_WINDOWS)
            endif()

            if (AS_USE_BOOST_LIBRARY)
                    target_link_libraries(${NAME} ${Boost_LIBRARIES})
            endif()

            if (AS_USE_STD_LIBRARY)
                    target_link_libraries(${NAME} -pthread)
            endif()

        endforeach(NAME)

endif()

#NOTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#Remember to add the path for the CxxTest installation director to your PATH environment variable
#
#CxxTest's user guide: http://cxxtest.com/cxxtest/doc/guide.html
#Good link on CxxTest setup http://wuhrr.wordpress.com/2008/01/15/how-to-set-up-cxxtest/
#
#For CxxTest on Windows: Install ActivePython and ActivePerl. You can find it here: \\vmpro1\SW Internet

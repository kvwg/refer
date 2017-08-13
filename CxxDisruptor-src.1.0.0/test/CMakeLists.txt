cmake_minimum_required(VERSION 2.8)

# Prevent warnings for full path libraries link
cmake_policy(SET CMP0003 NEW)

add_subdirectory(base)
add_subdirectory(atomic)
add_subdirectory(disruptor)


#NOTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#Remember to add the path for the CxxTest installation director to your PATH environment variable
#
#CxxTest's user guide: http://cxxtest.com/cxxtest/doc/guide.html
#Good link on CxxTest setup http://wuhrr.wordpress.com/2008/01/15/how-to-set-up-cxxtest/
#
#For CxxTest on Windows: Install ActivePython and ActivePerl. You can find it here: \\vmpro1\SW Internet

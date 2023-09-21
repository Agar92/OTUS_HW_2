file(GLOB test_cases *.cpp)
#set(test_cases "test_version.cpp")
foreach(case_file ${test_cases})
    get_filename_component( case_name ${case_file} NAME_WLE )
    message(${case_name})
    set (case_name ${case_name})
    add_executable(${case_name}_googletest ${case_file})
    target_link_libraries(${case_name}_googletest
      PUBLIC
        makeip
        version
        gtest_main
        pthread
    )

#    set_target_properties(${case_name}_googletest PROPERTIES
#    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
#    )
    target_include_directories(${case_name}_googletest
      PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${gtest_SOURCE_DIR}
        ${gtest_SOURCE_DIR}/include
    )

    target_compile_options(${case_name}_googletest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    add_test(NAME ${case_name}_googletest
             COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${case_name}_googletest
             WORKING_DIRECTORY
             ${PROJECT_BINARY_DIR}/tests)
    install(TARGETS ${case_name}_googletest DESTINATION tests)
endforeach()

add_test(NAME script
  COMMAND "${CMAKE_CURRENT_LIST_DIR}/script.sh" "${PROJECT_SOURCE_DIR}/ip_filter.tsv"
  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}")

#add_test(NAME test_version_googletest COMMAND ./test_version)

#find Python:
find_package(Python COMPONENTS Interpreter REQUIRED)
#execute Bash command from CMake and save the output to CMake variable:
execute_process (COMMAND bash -c "date +'%F %T'" OUTPUT_VARIABLE outVar)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/datestamp" "${outVar}")
#expected md5 control sum:
set(EXPECTED_RESULT "24e7a7b2270daee89c64d3ca5fb3da1a  -")
#!!!Multiple COMMAND calls inside execute_process are piped by default!!!
#call $cat ../OTUS_HW2/ip_filter.tsv | ./ip_filter | md5sum
#to find check sum of our project
execute_process(
    COMMAND cat ../OTUS_HW2/ip_filter.tsv
    COMMAND ./ip_filter
    COMMAND md5sum
    OUTPUT_VARIABLE RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE)
#compare our checksum with the expected one:
if( "${RESULT}" STREQUAL "${EXPECTED_RESULT}")
  message(STATUS "Congratulations! The MD5 checksum of the project equals the expected one!")
else()
  message(STATUS "Oops... The MD5 checksum of the project doesn't equal the expected one yet!")
endif()
#print our checksum:
message("RESULT=${RESULT}")
string(TIMESTAMP time "%Y-%m-%d   %H:%M:%S   %A")
message(STATUS "time=${time}")
#replace substring in string:
set(INPUT_STRING "/home/andrey/Desktop/build-OTUS_HW2")
string(REPLACE "OTUS_" "" OUT_STRING "${INPUT_STRING}")
message("OUT_STRING=${OUT_STRING}")

message("pwd=${CMAKE_CURRENT_BINARY_DIR}")

#add_custom_command(
#  OUTPUT o.cpp
#  COMMAND cat o.h > o.cpp
#  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#  DEPENDS o.h
#)
#add_custom_target(TARGET test_version_googletest
#    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    DEPENDS o.h
#)

# EVERY TIME YOU CHANGE tests/o.h,
# o.cpp is recreated andrey
# add_custom_command_example is rebuild!
# THIS COMMAND ALLOWS TO DO IT!
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/o.h")
message(STATUS "WARNING! Create o.h file in ${CMAKE_CURRENT_BINARY_DIR}")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/o.h"
"#include <iostream>

int main(int argc, char ** argv)
{
   return 0;
}"
)
else()
  message(STATUS "WARNING! File o.h already exists in ${CMAKE_CURRENT_BINARY_DIR}")
endif()
add_custom_command(
  OUTPUT o.cpp
  COMMAND cat o.h > o.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS o.h
)
add_executable(add_custom_command_example o.cpp)
target_include_directories(add_custom_command_example PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
#  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
#  VERBATIM)
#add_test(NAME PythonScript COMMAND ${Python_EXECUTABLE} run.py)

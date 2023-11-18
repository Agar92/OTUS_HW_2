file(GLOB test_cases *.cpp)

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

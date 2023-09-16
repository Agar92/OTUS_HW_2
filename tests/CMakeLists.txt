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
endforeach()

#add_test(NAME test_version_googletest COMMAND ./test_version)

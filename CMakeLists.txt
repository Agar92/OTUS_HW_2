cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 8.8.${PATCH_VERSION})

set(CMAKE_INSTALL_PREFIX  "/home/andrey/Desktop/install-OTUS_HW2")

project(ip_filter VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

message(STATUS "PROJECT_NAME=${PROJECT_NAME}")

option(CHANGE_APPROACH "Choose 1 of 2 approaches (ip_filter1/2.cpp files) for solving the problem" OFF)

add_subdirectory(MakeIP)
add_subdirectory(version)

if(CHANGE_APPROACH)
  add_subdirectory(comparator)
  add_executable(${PROJECT_NAME} ip_filter2.cpp)
  target_link_libraries(${PROJECT_NAME} PUBLIC comparator)
  message(STATUS "ip_filter2.cpp is compiled.")
else()
  message(STATUS "ip_filter1.cpp is compiled.")
  add_executable(${PROJECT_NAME} ip_filter1.cpp)
endif()

set_target_properties(${PROJECT_NAME}
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror
)


target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}")


target_link_libraries(${PROJECT_NAME} PRIVATE makeip)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ip_filter.tsv DESTINATION data)


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)


add_subdirectory(googletest)

enable_testing()

add_subdirectory(tests)

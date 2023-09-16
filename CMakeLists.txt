cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION 1.2.3)

configure_file(version.h.in version.h)

message(STATUS "PROJECT_NAME=${PROJECT_NAME}")

add_executable(${PROJECT_NAME} ip_filter.cpp)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror
)

add_subdirectory(MakeIP)
add_subdirectory(version)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}")


target_link_libraries(${PROJECT_NAME} PRIVATE makeip)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)


add_subdirectory(googletest)

enable_testing()

add_subdirectory(tests)

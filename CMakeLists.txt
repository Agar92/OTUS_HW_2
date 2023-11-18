cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 8.8.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)


add_subdirectory(MakeIP)
add_subdirectory(version)
add_subdirectory(comparator)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC comparator)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE makeip)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(FILES ip_filter.tsv DESTINATION data)


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)



include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)

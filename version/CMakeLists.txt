set(LIB "version")
add_library(${LIB} SHARED lib.cpp)

set_target_properties(${LIB}
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      CMAKE_INSTALL_PREFIX  "~/Desktop/install-OTUS_HW2/"
)

target_compile_options(${LIB} PRIVATE -Wall -Wextra -pedantic -Werror
)

target_include_directories(${LIB} PUBLIC ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
target_link_libraries(${LIB} PUBLIC makeip)

install(TARGETS ${LIB} LIBRARY DESTINATION lib)

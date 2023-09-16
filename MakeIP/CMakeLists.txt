set(LIB "makeip")
add_library(${LIB} SHARED makeip.cpp)
target_include_directories(${LIB} PUBLIC ${CMAKE_SOURCE_DIR})

set_target_properties(${LIB}
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      CMAKE_INSTALL_PREFIX  "~/Desktop/install-OTUS_HW2/"
)

target_compile_options(${LIB} PRIVATE -Wall -Wextra -pedantic -Werror
)
install(TARGETS ${LIB} LIBRARY DESTINATION lib)

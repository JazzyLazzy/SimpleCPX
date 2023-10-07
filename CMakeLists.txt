cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

include_directories(${CMAKE_BINARY_DIR}/src)

add_library(SimpleCPXParser SHARED src/SimpleCPXParser.c)

set_target_properties(SimpleCPXParser PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

install(TARGETS SimpleCPXParser DESTINATION lib)
install(FILES src/GPX.h DESTINATION include)

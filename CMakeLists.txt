cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

include_directories(/home/lazarus/Documents/SimpleCPX)

add_library(SimpleCPXParser SHARED SimpleCPXParser.c)

set_target_properties(SimpleCPXParser PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

install(TARGETS SimpleCPXParser DESTINATION lib)
install(FILES GPX.h DESTINATION include)

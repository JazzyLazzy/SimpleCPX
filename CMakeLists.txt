cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_INSTALL_PREFIX "/usr")

include_directories(${CMAKE_BINARY_DIR}/src)

add_library(SimpleCPXParser STATIC src/SimpleCPXParser.c)

set_target_properties(SimpleCPXParser PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_compile_options(SimpleCPXParser PRIVATE -fPIC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
message(STATUS "C Compiler Flags: ${CMAKE_C_FLAGS}")

#Comment to build for x86_64
include_directories(include)
link_directories(lib)
#target_link_libraries(SimpleCPXParser libexpat.so)

install(TARGETS SimpleCPXParser DESTINATION lib)
install(FILES src/GPX.h DESTINATION include)
install(FILES src/Location.h DESTINATION include)
install(FILES src/Waypoint.h DESTINATION include)
install(FILES src/Track.h DESTINATION include)
install(FILES src/Track_Seg.h DESTINATION include)
install(FILES src/SimpleCPXParser.h DESTINATION include)

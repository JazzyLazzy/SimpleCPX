cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_INSTALL_PREFIX "/usr")

include_directories(${CMAKE_BINARY_DIR}/src)

add_library(SimpleCPXParser SHARED src/SimpleCPXParser.c)

set_target_properties(SimpleCPXParser PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

install(TARGETS SimpleCPXParser DESTINATION lib)
install(FILES src/GPX.h DESTINATION include)
install(FILES src/Location.h DESTINATION include)
install(FILES src/Waypoint.h DESTINATION include)
install(FILES src/Track.h DESTINATION include)
install(FILES src/Track_Seg.h DESTINATION include)
install(FILES src/SimpleCPXParser.h DESTINATION include)

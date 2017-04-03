cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(EXEC_NAME "Pathfinder")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(${EXEC_NAME} CXX)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(${EXEC_NAME} ${SOURCES})
target_compile_features(${EXEC_NAME} PRIVATE cxx_range_for)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.2 REQUIRED system window graphics network audio)
target_link_libraries(${EXEC_NAME} ${SFML_LIBRARIES})

# Install target
install(TARGETS ${EXEC_NAME} DESTINATION bin)

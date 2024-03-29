cmake_minimum_required(VERSION 3.2.3)

project(rest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11 -fexceptions -pedantic -Wall -Wextra")

add_subdirectory(${PROJECT_SOURCE_DIR}/external/pistache)

include_directories(
    ${PROJECT_SOURCE_DIR}/external/pistache/install/include
    )

link_directories(
    ${PROJECT_SOURCE_DIR}/external/pistache/install/lib
    )

file(GLOB_RECURSE VAR_SOURCES ${PROJECT_SOURCE_DIR}/src/test/*.cpp)
set(VAR_SOURCES ${VAR_SOURCES} ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(${PROJECT_NAME} ${VAR_SOURCES})
add_dependencies(${PROJECT_NAME} pistache_ext)

target_link_libraries(${PROJECT_NAME} PUBLIC pthread stdc++ pistache)

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/install)

cmake_minimum_required(VERSION 3.0.0)
project(crafting_interpreters VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Lox.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scanner.cpp)

add_executable(crafting_interpreters)

target_sources(crafting_interpreters PUBLIC ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

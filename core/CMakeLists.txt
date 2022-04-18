cmake_minimum_required(VERSION 2.8)
project(core CXX)

set(${PROJECT_NAME}_SOURCES
    impl/core_impl.cpp
    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(${PROJECT_NAME}_DIRS
    ${CMAKE_SOURCE_DIR}
)


add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DIRS})
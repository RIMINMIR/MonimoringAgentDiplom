cmake_minimum_required(VERSION 2.8)
project(windows_service CXX)

set(${PROJECT_NAME}_SOURCES
    monitoring_agent.cpp
    windows_service.cpp
    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
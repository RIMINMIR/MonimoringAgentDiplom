cmake_minimum_required(VERSION 2.8)
project(windows_service CXX)

set(${PROJECT_NAME}_SOURCES
    monitoring_agent.cpp
    windows_service.cpp
    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(${PROJECT_NAME}_DIRS
    ${CMAKE_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DIRS})
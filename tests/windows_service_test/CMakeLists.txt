cmake_minimum_required(VERSION 2.8)
project(tests CXX)

set(${PROJECT_NAME}_SOURCES
    win_service_test.cpp
    )

set (${PROJECT_NAME}_Librari
)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(${PROJECT_NAME}_LIBS
    ${CONAN_LIBS_GTEST}
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIBS})
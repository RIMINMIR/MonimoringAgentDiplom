cmake_minimum_required(VERSION 2.8)
project(device_controller CXX)

set(${PROJECT_NAME}_SOURCES
    wmi_controller.cpp
    data_receiver.cpp
    ${CMAKE_SOURCE_DIR}/common/encoding_helper.cpp
    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(${PROJECT_NAME}_LIBS
    ${CONAN_LIBS_FMT}
)

set(PRIVATE_COMPILE_DEFINITIONS
CMAKE_BINPATH="${CMAKE_BINARY_DIR}"
)

set(${PROJECT_NAME}_DIRS
    ${CMAKE_SOURCE_DIR}
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PRIVATE_COMPILE_DEFINITIONS})

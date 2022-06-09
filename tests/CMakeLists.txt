cmake_minimum_required(VERSION 2.8)
project(tests CXX)

set(${PROJECT_NAME}_SOURCES
    event_queue_tests/event_queue_test.cpp
    windows_service_test/win_service_test.cpp
    device_controller_tests/wmi_controller_test.cpp
    core_tests/subsystem_run.cpp
    internal_storage/storage_test.cpp
    ${CMAKE_SOURCE_DIR}/common/encoding_helper.cpp
    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(${PROJECT_NAME}_LIBS
    ${CONAN_LIBS_GTEST}
    ${CONAN_LIBS_POCO}
    internal_storage
    device_controller
    core
)

set(PRIVATE_COMPILE_DEFINITIONS
CMAKE_BINPATH="${CMAKE_BINARY_DIR}"
)

set(${PROJECT_NAME}_DIRS
    ${CMAKE_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PRIVATE_COMPILE_DEFINITIONS})

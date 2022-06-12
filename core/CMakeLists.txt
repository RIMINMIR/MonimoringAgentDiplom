cmake_minimum_required(VERSION 2.8)
project(core CXX)

set(${PROJECT_NAME}_SOURCES
    impl/core_impl.cpp
    impl/event_controller_impl.cpp
    impl/monitoring_subsystem_impl.cpp
    impl/storage_controller_impl.cpp
    impl/transport_subsystem_impl.cpp
    #data collectors
    impl/data_collectors/disk_space_collector.cpp
    interface_factory.cpp
    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(${PROJECT_NAME}_DIRS
    ${CMAKE_SOURCE_DIR}
)

set(${PROJECT_NAME}_LIBS
    ${CONAN_LIBS_GTEST}
    internal_storage
    device_controller
)

set(PRIVATE_COMPILE_DEFINITIONS
CMAKE_SOURCE_PATH="${CMAKE_SOURCE_DIR}"
)


add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PRIVATE_COMPILE_DEFINITIONS})
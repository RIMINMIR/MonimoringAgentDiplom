cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(device_controller)

add_subdirectory(core)

add_subdirectory(windows_service)

add_subdirectory(tests)


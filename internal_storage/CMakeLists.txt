cmake_minimum_required(VERSION 2.8)
project(internal_storage CXX)

set(${PROJECT_NAME}_SOURCES

    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(${PROJECT_NAME}_LIBS
    ${CONAN_LIBS_GTEST}
    ${CONAN_LIBS_POCO}
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

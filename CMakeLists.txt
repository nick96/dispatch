cmake_minimum_required(VERSION 2.8.12)
project(dispatch C)

# Conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Common
file(GLOB COMMON_SRCS ${PROJECT_SOURCE_DIR}/common/*.c)
# add_library(common ${COMMON_SRCS})

# Source
file(GLOB DISPATCHCTLD_SRCS ${PROJECT_SOURCE_DIR}/dispatchctld/*.c)
add_executable(dispatchctld ${DISPATCHCTLD_SRCS})
target_include_directories(dispatchctld PRIVATE ${PROJECT_SOURCE_DIR}/common)
target_link_libraries(dispatchctld ${CONAN_LIBS_ZMQ})

file(GLOB DISPATCHD_SRCS ${PROJECT_SOURCE_DIR}/dispatchd/*.c)
add_executable(dispatchd ${DISPATCHD_SRCS})
target_include_directories(dispatchd PRIVATE ${PROJECT_SOURCE_DIR}/common)
target_link_libraries(dispatchd ${CONAN_LIBS_ZMQ})

file(GLOB DISPATCHCTL_SRCS ${PROJECT_SOURCE_DIR}/dispatchctl/*.c)
add_executable(dispatchctl ${DISPATCHCTL_SRCS})
target_include_directories(dispatchctl PRIVATE ${PROJECT_SOURCE_DIR}/common)
target_link_libraries(dispatchctl ${CONAN_LIBS_ZMQ})

# Tests
enable_testing()
list(REMOVE_ITEM DISPATCHCTLD_SRCS ${PROJECT_SOURCE_DIR}/dispatchctld/main.c)
list(REMOVE_ITEM DISPATCHD_SRCS ${PROJECT_SOURCE_DIR}/dispatchd/main.c)
file(GLOB TESTS ${PROJECT_SOURCE_DIR}/test/*.c)
add_executable(tests ${DISPATCHCTLD_SRCS} ${DISPATCHD_SRCS} ${TESTS})
target_link_libraries(tests ${CONAN_LIBS} -fsanitize=address -fsanitize=leak)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/common)
add_test(tests ${CMAKE_BINARY_DIR}/bin/tests)

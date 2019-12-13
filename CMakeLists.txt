cmake_minimum_required(VERSION 2.8.12)
project(dispatch C)

macro(src_tst_files SRC_VAR_NAME TST_VAR_NAME DIR)
  file(GLOB ${TST_VAR_NAME} ${DIR}/*_test.c)
  file(GLOB ${SRC_VAR_NAME} ${DIR}/*.c)
  list(FILTER ${SRC_VAR_NAME} EXCLUDE REGEX ".*_test.c$")
endmacro()

# Conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Source
src_tst_files(DISPATCHCTLD_SRCS DISPATCHCTLD_TSTS ${PROJECT_SOURCE_DIR}/dispatchctld)
add_executable(dispatchctld ${DISPATCHCTLD_SRCS})
target_link_libraries(dispatchctld ${CONAN_LIBS_ZMQ})

src_tst_files(DISPATCHD_SRCS DISPATCHD_TSTS ${PROJECT_SOURCE_DIR}/dispatchd)
add_executable(dispatchd ${DISPATCHD_SRCS})
target_link_libraries(dispatchd ${CONAN_LIBS_ZMQ})

# Tests
enable_testing()
add_executable(dispatchctld-test ${DISPATCHCTLD_SRCS} ${DISPATCHCTLD_TSTS})
target_link_libraries(dispatchctld-test ${CONAN_LIBS})
add_test(dispatchctld-test ${CMAKE_BINARY_DIR}/bin/dispatchctld-test)

add_executable(dispatchd-test ${DISPATCHD_SRCS} ${DISPATCHD_TSTS})
target_link_libraries(dispatchd-test ${CONAN_LIBS})
add_test(dispatchd-test ${CMAKE_BINARY_DIR}/bin/dispatchd-test)

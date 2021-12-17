project(VDSProject_test CXX C)
cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lgtest -lpthread ${LLVM_CXX_FLAGS} ")


include(install_gtest.cmake)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(.)


set(UNIT_TESTS main_test.cpp)
set(GTEST_LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
find_library(GTest GTest ${GTEST_LIB_DIR})
link_directories(${GTEST_LIB_DIR})


add_executable(VDSProject_test ${UNIT_TESTS})
target_link_libraries(VDSProject_test Manager)
target_link_libraries(VDSProject_test gtest gtest_main pthread)

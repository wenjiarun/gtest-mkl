cmake_minimum_required(VERSION 3.0)
project(gtest_mkl_example)
set(CMAKE_CXX_STANDARD 11)

set(MKLROOT "/home/fqss1804/intel/oneapi/mkl/2023.2.0")

# 添加头文件搜索路径和链接选项
include_directories(${MKLROOT}/include)
link_directories(${MKLROOT}/lib/intel64)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl")

# 添加源文件
add_executable(mytest gtest_mkl.cpp)
# 链接gtest和被测试的源文件
target_link_libraries(mytest ${GTEST_BOTH_LIBRARIES})

# 添加测试
enable_testing()
add_test(NAME my_gtest COMMAND mytest)

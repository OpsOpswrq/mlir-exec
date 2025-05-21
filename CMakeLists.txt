# 在CMakeLists.txt文件中，是不区分大小写
cmake_minimum_required(VERSION 3.20)
# 设置项目名称 和 版本 并且使用C++和C语言
project(MLIR_WRQ_learn LANGUAGES C CXX VERSION 1.0.0)
# 设置cmake策略
cmake_policy(SET CMP0116 NEW)
# 设置C语言标准 C17
set(CMAKE_C_STANDARD 17)
# 设置C++语言标准 C++17
set(CMAKE_CXX_STANDARD 20)
# 设置构建类型 设置构建类型为Release，强制执行
set(CMAKE_BUILD_TYPE "Release" CACHE STRING " " FORCE)
# 添加编译选项 启位置无关代码（PIC） 便于生成共享库
add_compile_options(-fPIC)
# 禁用RTTI 便于生成共享库
add_compile_options(-fno-rtti)
# 通过-DLLVM_DIR 和 -DMLIR_DIR 指定LLVM和MLIR的cmake安装路径
# LLVM_DIR 和 MLIR_DIR 
find_package(LLVM REQUIRED CONFIG)
find_package(MLIR REQUIRED CONFIG)
# 将LLVM_DIR 和 MLIR_DIR 添加到CMAKE_MODULE_PATH中
list(APPEND CMAKE_MODULE_PATH "${LLVM_DIR}")
list(APPEND CMAKE_MODULE_PATH "${MLIR_DIR}")
# 包含LLVM 和 MLIR 的cmake模块 下面的这些都是cmake文件名字
include(AddLLVM)
include(AddMLIR)
include(TableGen)
include(HandleLLVMOptions)
include(LLVMConfig)
include(MLIRConfig)
# 包含LLVM 和 MLIR 的头文件
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
# 获取MLIR的dialect、conversion、extension库
# 在对应MLIRConfig.cmake 文件中
get_property(all_libs GLOBAL PROPERTY MLIR_ALL_LIBS)
get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
get_property(extension_libs GLOBAL PROPERTY MLIR_EXTENSION_LIBS)
get_property(translation_libs GLOBAL PROPERTY MLIR_TRANSLATION_LIBS)
# 之后可能通过这个操作将链接库进行链接
# target_link_libraries(your_target ${dialect_libs} ${conversion_libs} ${extension_libs})
# 添加子目录
add_subdirectory(ex0-define_dialect)
add_subdirectory(ex1-define_type)
add_subdirectory(ex2-define_attribute)
add_subdirectory(ex3-define_operation)
add_subdirectory(ex4-define_pass)
add_subdirectory(ex5-rewrite_pattern)
add_subdirectory(ex6-lit_for_test)
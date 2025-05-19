# 这一节先定义自己的方言
set(EXEC 1)
# 包括当前可执行文件的头文件
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
# 包括当前源文件的头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# 包括下级文件夹
add_subdirectory(include)
add_subdirectory(lib)
# 添加可执行文件
add_executable(Exec-${EXEC} "main.cpp")
# 添加依赖库文件
target_link_libraries(Exec-${EXEC} 
        PUBLIC MLIRExecDialect${EXEC})
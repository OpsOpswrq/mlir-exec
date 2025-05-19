#!/bin/bash
NAME=${1}
mkdir -p build
cd build
# 暂时export
export LLVM_INSTALL_DIR=/home/workspace/wrq/third_party/llvm_install
export LLVM_DIR=${LLVM_INSTALL_DIR}/lib/cmake/llvm
export MLIR_DIR=${LLVM_INSTALL_DIR}/lib/cmake/mlir
# 这是依赖于llvm自己的llvm-lit工具
export LLVM_BUILD_DIR=/home/workspace/wrq/third_party/llvm-project/build

cmake -G Ninja .. \
    -DLLVM_DIR=${LLVM_DIR} \
    -DMLIR_DIR=${MLIR_DIR} \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_EXTERNAL_LIT=$LLVM_BUILD_DIR/bin/llvm-lit \
    -DCMAKE_INSTALL_PREFIX=${LLVM_INSTALL_DIR}
# -DCMAKE_INSTALL_PREFIX 指定安装目录
if [ ${NAME} == "all" ]; then
    ninja -j 4 # 指定8个线程进行编译处理
else
    ninja -j 4 ${NAME}
fi
# 教程位置：https://github.com/violetDelia/MLIR-Tutorial

#ifndef LIB_DIALECT_EXEC_IR_EXECDIALECT_CPP
#define LIB_DIALECT_EXEC_IR_EXECDIALECT_CPP
#include "Dialect/Exec/IR/ExecDialect.h"
#include "Dialect/Exec/IR/ExecTypes.h"
#include "Dialect/Exec/IR/ExecAttrs.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/StringRef.h"
#define FIX
#include "Dialect/Exec/IR/ExecDialect.cpp.inc"
#undef FIX

namespace mlir::exec{
    // 每个Dialect必须实现的方法，属于初始化的方法
    void ExecDialect::initialize(){
        llvm::outs() << "Hello World! Here is ExecDialect, I am for the purpose of exercise! \n";
        registerTypes(); // 注册自定义类型
        registerAttrs(); // 注册自定义属性
    }
    // 需要实现的方法
    void ExecDialect::sayHello(llvm::StringRef name){
        llvm::outs() << "Hello! " << name << "!\n";
    }
    // 需要实现的析构函数
    ExecDialect::~ExecDialect(){
        llvm::outs() << "Good Bye! \n";
    } 
}

#endif // LIB_DIALECT_EXEC_IR_EXECDIALECT_CPP
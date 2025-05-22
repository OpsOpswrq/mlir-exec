#ifndef LIB_DIALECT_EXEC_IR_EXECOPS_CPP
#define LIB_DIALECT_EXEC_IR_EXECOPS_CPP
#include "Dialect/Exec/IR/ExecDialect.h"
#include "Dialect/Exec/IR/ExecAttrs.h"
#include "Dialect/Exec/IR/ExecOps.h"
#include "Dialect/Exec/IR/ExecTypes.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/TypeSwitch.h"
#include "mlir/IR/BuiltinTypeInterfaces.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/OpImplementation.h"
#include "llvm/Support/LogicalResult.h"
#include "mlir/Support/LLVM.h"
#include "mlir/IR/Operation.h"
#define FIX
#define GET_OP_CLASSES
#include "Dialect/Exec/IR/ExecOps.cpp.inc"
namespace mlir::exec{
    void ExecDialect::registerOps(){
        llvm::outs() << "register " << getDialectNamespace() << " Operation\n";
        addOperations<
            #define GET_OP_LIST
            #include "Dialect/Exec/IR/ExecOps.cpp.inc"
        >();
    }
    // 这个名字可以直接看h.inc文件中，怎么写的，它怎么写，你就怎么写就行
    LogicalResult AddOp::verify(){ 
        if (getLhs().getType() != getRhs().getType())
            return emitOpError("requires the same type for lhs and rhs");

        if (getResult().getType() != getLhs().getType())
            return emitOpError("result type must match operand types");
        
        return success();
    }
}
#undef FIX
#endif // LIB_DIALECT_EXEC_IR_EXECOPS_CPP
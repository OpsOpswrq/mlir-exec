#ifndef LIB_DIALECT_EXEC_IR_EXECATTRS_CPP
#define LIB_DIALECT_EXEC_IR_EXECATTRS_CPP

#include "mlir/IR/BuiltinAttributes.h"
#include "Dialect/Exec/IR/ExecDialect.h"
#include "Dialect/Exec/IR/ExecTypes.h"
#include "Dialect/Exec/IR/ExecAttrs.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/IR/BuiltinTypeInterfaces.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/Support/LLVM.h"
#include "llvm/ADT/TypeSwitch.h"
#define FIX
#define GET_ATTRDEF_CLASSES
#include "Dialect/Exec/IR/ExecAttrs.cpp.inc" // 定义 builder、parser、printer
namespace mlir::exec{
    void ExecDialect::registerAttrs(){
        llvm::outs() << "register " << getDialectNamespace() << " Attr\n";
        addAttributes<
            #define GET_ATTRDEF_LIST
            #include "Dialect/Exec/IR/ExecAttrs.cpp.inc"
        >();
    }
    // 在td文件中使用了genVerifyDecl属性，所以需要使用到verify方法
    LogicalResult ExecCIntAttr::verify(function_ref<InFlightDiagnostic()> emitError, int64_t cnt){
        if(cnt <= 0){
            return emitError() << "the cnt attribute is must bigger than zero \n";
        }
        return success();
    }
}
#undef FIX
#endif // LIB_DIALECT_EXEC_IR_EXECATTRS_CPP
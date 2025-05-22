#ifndef INCLUDE_DIALECT_EXEC_IR_EXECCONSTRAINTS_TD
#define INCLUDE_DIALECT_EXEC_IR_EXECCONSTRAINTS_TD

include "mlir/IR/CommonTypeConstraints.td"
include "mlir/IR/CommonAttrConstraints.td"
include "mlir/IR/OpBase.td"
include "Dialect/Exec/IR/ExecTypes.td"
include "Dialect/Exec/IR/ExecAttrs.td"

// 其他情况有verify限制，现在就是强制使用自定义的type 和 attribute
def ExecOpsTypeConstraint : Type<CPred<"isa<::mlir::exec::ExecIntType>($_self)">, "Type constraint, just for test">;
// 这个部分看源码就知道怎么写了 CommonAttrConstraints
def ExecOpsAttrConstraint : Attr<CPred<"isa<::mlir::exec::ExecCIntAttr>($_self)">, "Attribute constraint, just for test">{
    code storageType = "mlir::exec::ExecCIntAttr";
    code returnType = "mlir::exec::ExecCIntAttr";
    code convertFromStorage = "$_self";
}

#endif // INCLUDE_DIALECT_EXEC_IR_EXECCONSTRAINTS_TD
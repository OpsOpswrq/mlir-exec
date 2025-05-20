#ifndef INCLUDE_DIALECT_EXEC_IR_EXECOPS_TD
#define INCLUDE_DIALECT_EXEC_IR_EXECOPS_TD
// 添加相应的头文件
include "mlir/IR/BuiltinDialect.td"
include "mlir/IR/Constraints.td"
include "mlir/IR/OpBase.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/Interfaces/SideEffectInterfaces.td"
// 添加自定义操作所需的头文件
include "Dialect/Exec/IR/ExecDialect.td"
include "Dialect/Exec/IR/ExecAttrs.td"
include "Dialect/Exec/IR/ExecTypes.td"
include "Dialect/Exec/IR/ExecConstraints.td"

// 定义操作基类
class Exec_Ops<string mnemonic, list<Trait> traits = []>
    : Op<Exec_Dialect, mnemonic, traits>;

// 抽象的二元操作模板：用于定义类似 Add/Sub/Mul 等操作
class Exec_BinaryOps<string mnemonic, Type operandType, Type resultType = operandType,
                     list<Trait> traits = [], dag attributes = (ins)>
    : Exec_Ops<mnemonic, traits#[]> {
    let summary = !strconcat(mnemonic, " operation on ExecIntType");
    let description = !strconcat("Performs ", mnemonic, " on two ExecIntType operands with optional attributes.");

    let hasVerifier = 1;

    // 链接的内容
    let arguments = !con((ins
        operandType:$lhs,
        operandType:$rhs),
        attributes
    );

    let results = (outs
        resultType:$result
    );

    let skipDefaultBuilders = 1;

    let builders = [
        OpBuilder<(ins
            "Type":$resultType,
            "Value":$lhs,
            "Value":$rhs,
            "Attribute":$cntAttr
        )>,
        OpBuilder<(ins
            "OpBuilder &":$builder,
            "OperationState &":$state,
            "Value":$lhs,
            "Value":$rhs,
            "int64_t":$cnt
        ), [{
            auto cntAttr = ::mlir::exec::ExecCIntAttr::get(builder.getContext(), cnt);
            auto resultType = lhs.getType();
            state.addOperands({lhs, rhs});
            state.addTypes(resultType);
            state.addAttribute("cnt", cntAttr);
        }]>
    ];

}


// 加法操作
// 后续需要修改，接着修改
def Exec_AddOp : Exec_BinaryOps<"ExecAdd",
    ExecOpsTypeConstraint, ExecOpsTypeConstraint,
    [Pure, SameOperandsAndResultType],
    (ins I64Attr:$cnt)> {
    let summary = "Addition for ExecIntType";
}

#endif // INCLUDE_DIALECT_EXEC_IR_EXECOPS_TD
#ifndef INCLUDE_DIALECT_EXEC_IR_EXECOPS_TD
#define INCLUDE_DIALECT_EXEC_IR_EXECOPS_TD

// Include required header files
include "mlir/IR/BuiltinDialect.td"
include "mlir/IR/Constraints.td"
include "mlir/IR/OpBase.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

// Include custom operation required header files
include "Dialect/Exec/IR/ExecDialect.td"
include "Dialect/Exec/IR/ExecAttrs.td"
include "Dialect/Exec/IR/ExecTypes.td"
include "Dialect/Exec/IR/ExecConstraints.td"

// Define base operation class
class Exec_Ops<string mnemonic, list<Trait> traits = []>
    : Op<Exec_Dialect, mnemonic, traits>;

// 这里的大部分都是默认处理的
def Exec_WrapIntOp : Exec_Ops<"wrap", [Pure]> {
  let arguments = (ins SignlessIntegerLike:$input);
  let results = (outs ExecOpsTypeConstraint:$result);
}

// Abstract binary operation template: for operations like Add/Sub/Mul
class Exec_BinaryOps<string mnemonic, Type operandType, Type resultType = operandType,
                     list<Trait> traits = [], dag attributes = (ins)>
    : Exec_Ops<mnemonic, traits#[]> {
    let summary = !strconcat(mnemonic, " operation on ExecIntType");
    let description = !strconcat("Performs ", mnemonic, " on two ExecIntType operands with optional attributes.");

    let hasVerifier = 1;

    // Arguments definition
    let arguments = !con((ins
        operandType:$lhs,
        operandType:$rhs),
        attributes
    );

    let results = (outs
        resultType:$result
    );

    let skipDefaultBuilders = 1;
    
    // Custom builder methods
    let builders = [
        // 自定义构建器 1：使用操作数和属性创建操作
        OpBuilder<(ins "Value":$lhs, "Value":$rhs, "::mlir::exec::ExecCIntAttr":$cnt),
        [{
            $_state.addOperands({lhs, rhs});
            $_state.addAttribute("cnt", cnt);
            $_state.addTypes({lhs.getType()});
        }]>,
        
        // 自定义构建器 2：使用操作数和整数值创建操作
        OpBuilder<(ins "Value":$lhs, "Value":$rhs, "int64_t":$cntVal),
        [{
            $_state.addOperands({lhs, rhs});
            auto cntAttr = ::mlir::exec::ExecCIntAttr::get($_builder.getContext(), cntVal);
            $_state.addAttribute("cnt", cntAttr);
            $_state.addTypes({lhs.getType()});
        }]>,
        
        // 自定义构建器 3：仅使用操作数创建操作，使用默认属性值
        OpBuilder<(ins "Value":$lhs, "Value":$rhs),
        [{
            $_state.addOperands({lhs, rhs});
            auto cntAttr = ::mlir::exec::ExecCIntAttr::get($_builder.getContext(), 1);
            $_state.addAttribute("cnt", cntAttr);
            $_state.addTypes({lhs.getType()});
        }]>
    ];
}

// Addition operation definition
def Exec_AddOp : Exec_BinaryOps<"ExecAdd",
    ExecOpsTypeConstraint, ExecOpsTypeConstraint,
    [Pure, SameOperandsAndResultType],
    (ins ExecOpsAttrConstraint:$cnt)> {
    let summary = "Addition for ExecIntType";
    let description = [{
        The ExecAdd operation performs addition of two exec.int values with a count attribute.
        
        Example:
        ```mlir
        %result = exec.ExecAdd %a, %b { cnt = 42 } : !exec.int
        ```
    }];
}

#endif // INCLUDE_DIALECT_EXEC_IR_EXECOPS_TD
#ifndef INCLUDE_DIALECT_EXEC_TRANSFORMS_PASSES_TD
#define INCLUDE_DIALECT_EXEC_TRANSFORMS_PASSES_TD
include "mlir/Pass/PassBase.td"
include "Dialect/Exec/IR/ExecOps.td"
// 定义pass
def ExecTestPass : Pass<"apply-pass-in-exec">{
    let summary = "Test define a pass for the dialect exec";
    let description = [{
        Just for the exercise, define a pass for the dialect exec
    }];
    let dependentDialects = [
        "arith::ArithDialect",
        "scf::SCFDialect"
    ];
    let options = [
        Option<
            /*C++ variable name*/"option",
            /*argument*/"example-option",
            /*type C++ type*/"bool",
            /*default value*/"true",
            /*description*/"An example option"
        >,
    ];
    // 构建一个默认pass实例
    let constructor = "::mlir::exec::createExecPasses()";
}

#endif // INCLUDE_DIALECT_EXEC_TRANSFORMS_PASSES_TD
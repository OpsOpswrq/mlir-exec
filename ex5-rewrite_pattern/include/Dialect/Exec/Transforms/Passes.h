#ifndef INCLUDE_DIALECT_EXEC_TRANSFORMS_PASSES_H
#define INCLUDE_DIALECT_EXEC_TRANSFORMS_PASSES_H

#include "mlir/Pass/Pass.h"
#include "mlir/IR/MLIRContext.h"
#include "Dialect/Exec/IR/ExecOps.h"
// 按照源码结构来
namespace mlir::exec{
    #define GEN_PASS_DECL
    #include "Dialect/Exec/Transforms/Passes.h.inc"
    std::unique_ptr<mlir::Pass> createExecPasses();
    #define GEN_PASS_REGISTRATION
    #include "Dialect/Exec/Transforms/Passes.h.inc"
}
#endif // INCLUDE_DIALECT_EXEC_TRANSFORMS_PASSES_H
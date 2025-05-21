#ifndef INCLUDE_DIALECT_EXEC_TRANSFORMS_PASSES_CPP
#define INCLUDE_DIALECT_EXEC_TRANSFORMS_PASSES_CPP

#include "Dialect/Exec/Transforms/Passes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"

namespace mlir::exec{
    // 这个名字按照实际情况来更改
    #define GEN_PASS_DEF_EXECTESTPASS
    #include "Dialect/Exec/Transforms/Passes.h.inc"
}
using namespace mlir;
using namespace mlir::exec;
struct ExecTestPass : ::mlir::exec::impl::ExecTestPassBase<ExecTestPass>{
    using ExecTestPassBase<ExecTestPass>::ExecTestPassBase; // 使用相应的构造函数
    void runOnOperation() override;
};
void ExecTestPass::runOnOperation(){
    llvm::outs() << "run in: " << getPassName() << "\n";
    auto func = getOperation();
    llvm::outs() << "root op: " << func->getName() << "\n";
}
std::unique_ptr<mlir::Pass> mlir::exec::createExecPasses(){
    return std::make_unique<ExecTestPass>();
}

#endif // INCLUDE_DIALECT_EXEC_TRANSFORMS_PASSES_CPP
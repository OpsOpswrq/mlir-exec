#ifndef INCLUDE_DIALECT_EXEC_TRANSFORMS_APPLYREWRITEPATTERN_CPP
#define INCLUDE_DIALECT_EXEC_TRANSFORMS_APPLYREWRITEPATTERN_CPP

#include "Dialect/Exec/Transforms/Passes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/PatternMatch.h" // 这个是主要文件
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "llvm/Support/LogicalResult.h"

namespace mlir::exec{
    // 这个名字按照实际情况来更改
    #define GEN_PASS_DEF_EXECTESTPASS
    #include "Dialect/Exec/Transforms/Passes.h.inc"
}
using namespace mlir;
using namespace mlir::exec;
// 假设你已经定义并注册了 WrapIntOp（需要你自己实现）

struct ApplyRewritePatternForExecAddOp : public OpRewritePattern<::mlir::exec::AddOp> {
    using OpRewritePattern::OpRewritePattern;

    LogicalResult matchAndRewrite(::mlir::exec::AddOp op, PatternRewriter &rewriter) const override {
        llvm::outs() << "match: " << getDebugName() << "\n";

        auto lhsType = op.getLhs().getType().dyn_cast<::mlir::exec::ExecIntType>();
        auto rhsType = op.getRhs().getType().dyn_cast<::mlir::exec::ExecIntType>();
        if (!lhsType || !rhsType)
            return failure();

        auto cntAttr = op.getCntAttr();
        int64_t cntValue = cntAttr.getCnt();
        if (cntValue < 0) {
            llvm::outs() << "  Skip already rewritten op (cnt < 0)\n";
            return failure();
        }

        int64_t lhsValue = lhsType.getInput();
        int64_t rhsValue = rhsType.getInput();
        llvm::outs() << "  Computed " << lhsValue << " + " << rhsValue << " = " << (lhsValue + rhsValue) << "\n";

        Location loc = op.getLoc();

        unsigned width = lhsType.getWidth();
        auto intType = IntegerType::get(rewriter.getContext(), width);  // signless i64

        auto lhsConst = rewriter.create<arith::ConstantOp>(
            loc, intType, rewriter.getIntegerAttr(intType, lhsValue * cntValue));
        auto rhsConst = rewriter.create<arith::ConstantOp>(
            loc, intType, rewriter.getIntegerAttr(intType, rhsValue * cntValue));

        auto addOp = rewriter.create<arith::AddIOp>(loc, lhsConst, rhsConst);

        // 封装为 ExecIntType 为了成功转换 type是不可变的
        auto execType = ::mlir::exec::ExecIntType::get(rewriter.getContext(), width, lhsValue);
        auto wrapped = rewriter.create<::mlir::exec::WrapIntOp>(loc, execType, addOp.getResult());
        // 这里转换成了另一个函数，所以就不再继续匹配了
        rewriter.replaceOp(op, wrapped.getResult());

        return success();
    }
};



struct ExecTestPass : ::mlir::exec::impl::ExecTestPassBase<ExecTestPass>{
    using ExecTestPassBase<ExecTestPass>::ExecTestPassBase; // 使用相应的构造函数
    void runOnOperation() override;
};
// 运算重载函数 在这个函数中添加相应的rewrite pattern
void ExecTestPass::runOnOperation(){
    llvm::outs() << "run in: " << getPassName() << "\n";
    auto func = getOperation();
    MLIRContext *context = &getContext();
            
    // Create a RewritePatternSet and add our pattern to it
    // 这个地方需要添加自定义的rewrite pattern
    RewritePatternSet patterns(context);
    patterns.add<ApplyRewritePatternForExecAddOp>(context);
    
    // Apply the patterns using the GreedyRewriteConfig
    if (failed(applyPatternsAndFoldGreedily(func, std::move(patterns)))) {
        signalPassFailure();
    }
    llvm::outs() << "root op: " << func->getName() << "\n";
}
std::unique_ptr<mlir::Pass> mlir::exec::createExecPasses(){
    return std::make_unique<ExecTestPass>();
}
#endif // INCLUDE_DIALECT_EXEC_TRANSFORMS_APPLYREWRITEPATTERN_CPP
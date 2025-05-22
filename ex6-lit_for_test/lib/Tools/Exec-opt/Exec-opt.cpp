#include "mlir/Config/mlir-config.h"
#include "mlir/IR/AsmState.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllExtensions.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Target/LLVMIR/Dialect/All.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "Dialect/Exec/IR/ExecDialect.h"
#include "Dialect/Exec/Transforms/Passes.h"


int main(int argc, char** argv){
    mlir::DialectRegistry registry;
    registerAllDialects(registry);
    registry.insert<mlir::exec::ExecDialect>();
    // 注册所定义的pass
    mlir::exec::registerPasses();
    return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "Exec modular optimizer driver\n", registry));
}
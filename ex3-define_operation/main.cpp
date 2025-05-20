// 程序入口文件
#include "mlir/IR/MLIRContext.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "llvm/Support/raw_ostream.h"
#include "Dialect/Exec/IR/ExecDialect.h"
#include "Dialect/Exec/IR/ExecTypes.h"
#include "Dialect/Exec/IR/ExecAttrs.h"
#include "Dialect/Exec/IR/ExecOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/DialectRegistry.h"

#include <cstdlib>   // std::atoi
#include <iostream>  // std::cerr

void Exec0(llvm::StringRef name) {
    mlir::DialectRegistry registry;
    registry.insert<mlir::exec::ExecDialect>();
    mlir::MLIRContext context(registry);

    auto *dialect = context.getOrLoadDialect<mlir::exec::ExecDialect>();
    dialect->sayHello(name);
}

void Exec1(llvm::StringRef name, int64_t integerInput, unsigned width = 16) {
    mlir::DialectRegistry registry;
    registry.insert<mlir::exec::ExecDialect>();
    mlir::MLIRContext context(registry);

    auto *dialect = context.getOrLoadDialect<mlir::exec::ExecDialect>();
    dialect->sayHello(name);

    auto eInt = mlir::exec::ExecIntType::get(&context, width, integerInput);
    llvm::outs() << "ExecIntType : ";
    eInt.dump();
}

void Exec2(llvm::StringRef name, int64_t integerInput, unsigned width = 16, int64_t cnt = 1){
    mlir::DialectRegistry registry;
    registry.insert<mlir::exec::ExecDialect>();
    mlir::MLIRContext context(registry);

    auto *dialect = context.getOrLoadDialect<mlir::exec::ExecDialect>();
    dialect->sayHello(name);

    auto eInt = mlir::exec::ExecIntType::get(&context, width, integerInput);
    llvm::outs() << "ExecIntType : ";
    eInt.dump();
    
    auto eCInt = mlir::exec::ExecCIntAttr::get(&context, cnt);
    llvm::outs() << "ExecCIntAttr : ";
    eCInt.dump();
}

void Exec3(llvm::StringRef name, int64_t lhs, int64_t rhs, unsigned width = 16, int64_t cnt = 1){
    mlir::DialectRegistry registry;
    registry.insert<mlir::func::FuncDialect>();
    registry.insert<mlir::exec::ExecDialect>();
    mlir::MLIRContext context(registry);

    auto *dialect = context.getOrLoadDialect<mlir::exec::ExecDialect>();
    dialect->sayHello(name);

    auto execTy = mlir::exec::ExecIntType::get(&context, width, lhs);
    auto cntAttr = mlir::exec::ExecCIntAttr::get(&context, cnt);

    mlir::OpBuilder builder(&context);
    auto loc = builder.getUnknownLoc();

    auto module = builder.create<mlir::ModuleOp>(loc, "Exec");
    builder.setInsertionPointToStart(module.getBody());

    // 创建一个函数用于放置 AddOp
    // auto funcType = builder.getFunctionType({}, {});
    // auto func = builder.create<mlir::func::FuncOp>(loc, "test_add", funcType);
    // auto &entryBlock = *func.addEntryBlock();

    // builder.setInsertionPointToStart(&entryBlock);
    // 这里定义相应的操作出现问题
    // // 添加两个 block 参数作为 lhs 和 rhs
    // auto lhsVal = entryBlock.addArgument(execTy, loc);
    // auto rhsVal = entryBlock.addArgument(execTy, loc);

    // auto addOp = builder.create<mlir::exec::AddOp>(
    //     loc,
    //     execTy,
    //     lhs,
    //     rhs,
    //     cntAttr
    // );

    // llvm::outs() << "Created AddOp:\n";
    // addOp.dump();
}


int main(int argc, char **argv) {
    if (argc == 2) {
        Exec0(argv[1]);
    } else if (argc == 3) {
        std::cout << argv[3] << std::endl;
        int64_t input = std::atoi(argv[2]);
        Exec1(argv[1], input);
    } else if (argc == 4) {
        int64_t input = std::atoi(argv[2]);
        unsigned width = static_cast<unsigned>(std::atoi(argv[3]));
        Exec1(argv[1], input, width);
    } else if (argc == 5) {
        int64_t input = std::atoi(argv[2]);
        unsigned width = static_cast<unsigned>(std::atoi(argv[3]));
        int64_t cnt = std::atoi(argv[4]);
        Exec2(argv[1], input, width, cnt);
    } else if (argc == 6 ) {
        int64_t lhs = std::atoi(argv[2]);
        int64_t rhs = std::atoi(argv[3]);
        unsigned width = static_cast<unsigned>(std::atoi(argv[4]));
        int64_t cnt = std::atoi(argv[5]);
        Exec3(argv[1], lhs, rhs, width, cnt);
    } else {
        std::cerr << "Usage:\n"
                  << "  " << argv[0] << " <name>\n"
                  << "  " << argv[0] << " <name> <int>\n"
                  << "  " << argv[0] << " <name> <int> <width>\n";
        return 1;
    }
    return 0;
}

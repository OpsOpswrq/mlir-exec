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
#include "mlir/IR/BuiltinTypes.h"

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

void Exec3(llvm::StringRef name, int64_t lhsValue, int64_t rhsValue, unsigned width = 16, int64_t cnt = 1) {
    // 创建上下文并加载方言
    mlir::MLIRContext context;
    context.loadDialect<mlir::func::FuncDialect>();
    context.loadDialect<mlir::exec::ExecDialect>();
    
    // 获取方言并打印欢迎信息
    auto *dialect = context.getLoadedDialect<mlir::exec::ExecDialect>();
    dialect->sayHello(name);
    
    // 创建构建器和位置
    mlir::OpBuilder builder(&context);
    auto loc = builder.getUnknownLoc();
    
    // 创建模块
    auto module = builder.create<mlir::ModuleOp>(loc);
    builder.setInsertionPointToStart(module.getBody());
    
    // 创建类型
    auto lhsType = mlir::exec::ExecIntType::get(&context, width, lhsValue);
    auto rhsType = mlir::exec::ExecIntType::get(&context, width, rhsValue);
    // 创建函数类型，包含两个参数，一个返回值
    auto funcType = builder.getFunctionType({lhsType, rhsType}, {lhsType});
    auto func = builder.create<mlir::func::FuncOp>(loc, "test_add", funcType);
    
    // 添加入口块
    auto &entryBlock = *func.addEntryBlock();
    builder.setInsertionPointToStart(&entryBlock);
    
    // 获取块参数作为操作数（这些是函数参数，而不是常量）
    auto lhsVal = entryBlock.getArgument(0);
    auto rhsVal = entryBlock.getArgument(1);
    
    // 创建 cnt 属性
    auto cntAttr = mlir::exec::ExecCIntAttr::get(&context, cnt);
    
    // 创建 AddOp 操作
    auto addOp = builder.create<mlir::exec::AddOp>(
        loc,
        lhsVal,
        rhsVal,
        cntAttr
    );
    
    // 创建返回操作，返回 addOp 的结果
    builder.create<mlir::func::ReturnOp>(loc, addOp.getResult());
    
    // 打印创建的操作和模块
    llvm::outs() << "Created AddOp:\n";
    addOp.dump();
    
    llvm::outs() << "\nCreated module:\n";
    module.dump();
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

// 程序的入口文件
// 必须有的MLIR语境文件
#include "mlir/IR/MLIRContext.h"
// 相应的方言文件
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "llvm/Support/raw_ostream.h"
#include "Dialect/Exec/IR/ExecDialect.h"
void Exec0(llvm::StringRef name){
    mlir::DialectRegistry registry;
    mlir::MLIRContext context(registry);
    // 加载/注册方言
    // 对应类型dialect类型 指针类型的
    auto dialect = context.getOrLoadDialect<mlir::exec::ExecDialect>();
    // 调用方言中的方法
    dialect->sayHello(name);
}
int main(int argc, char** argv){
    if(argc > 1){
        Exec0(llvm::StringRef(argv[1])); // char** 转 string，再转StringRef
    }
    return 0;
}
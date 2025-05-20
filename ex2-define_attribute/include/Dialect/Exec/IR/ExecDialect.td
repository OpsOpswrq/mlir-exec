#ifndef INCLUDE_DIALECT_EXEC_IR_EXECDIALECT_TD
#define INCLUDE_DIALECT_EXEC_IR_EXECDIALECT_TD
// 添加方言文件
include "mlir/IR/DialectBase.td"
// 这里tablegen会自动转换名字为ExecDialect，即按照模式匹配，进行字符串拼接
def Exec_Dialect : Dialect{
    // 方言的名字
    let name = "Exec_Dialect";
    // 方言的简介
    let summary = "Exec_Dialect is for me to exercise and be familiar with the procedure of mlir";
    // 方言的命名空间 ::是全局作用域解析运算符
    let cppNamespace = "::mlir::exec";
    // 这个方言它依赖的方言是基于哪个方言的
    let dependentDialects = [
        "arith::ArithDialect"
    ];
    // 在无法自动生成的代码中，需要使用到下面这个选项来进行后续操作
    // 自定义方法内容 直接嵌入到C++代码中，所以，无需引入相应的头文件
    let extraClassDeclaration = [{
        void sayHello(llvm::StringRef name);
        void registerTypes(); // 添加对应的自定义类型
        void registerAttrs(); // 添加相应的属性类型
    }];
    // 自己自定义了一个析构函数，不使用默认的析构函数
    let hasNonDefaultDestructor = 1;
    // 使用MLIR默认的类型解析输出.
    let useDefaultTypePrinterParser = 1;
    // 使用MLIR默认的属性解析输出
    let useDefaultAttributePrinterParser = 1;
}

#endif // INCLUDE_DIALECT_EXEC_IR_EXECDIALECT_TD
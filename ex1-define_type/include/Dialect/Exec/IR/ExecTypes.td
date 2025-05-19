#ifndef DIALECT_EXEC_IR_EXECTYPES_TD
#define DIALECT_EXEC_IR_EXECTYPES_TD
// 加上自定义方言头文件
include "Dialect/Exec/IR/ExecDialect.td"
// 自定义类型头文件
include "mlir/IR/AttrTypeBase.td"
// 这个是类型基类 baseClass
// 这个有默认参数
class Exec_Type<string name, string typeMnemonic, list<Trait> traits = [], string baseCppClass = "::mlir::Type">
    : TypeDef<Exec_Dialect, name, traits, baseCppClass>{
    let mnemonic = typeMnemonic;
    // # 是链接符，链接字符串的内容
    string typeName = dialect.name # "." # typeMnemonic;
}

// 下面开始自定义需要的类型了 def 开始定义了
def Exec_IntType : Exec_Type<"ExecInt", "eInt", []>{
    let summary = "Exec_Dialect Int Type";
    let description = [{
        Just for exercise! To represent the Integer and Width
    }];
    // ins是输入的意思 一个宽度 一个int大小
    let parameters = (ins
        "unsigned":$width, // 8 16 32 64等等
        "int64_t":$input
    );
    // 这个是设置get钩子方法，对应于getWidth等方法
    let genStorageClass = 1;
    // 不建议改动 是否有自定义构造函数
    let hasStorageCustomConstructor = 0;
    let builders = [
        TypeBuilder<(ins
            "unsigned":$width,
            "int64_t":$input
        )>
    ];
    // 自定义表达方式 printer 和 parser的方法
    let hasCustomAssemblyFormat = 1;
    // 是否跳过默认的builder函数
    let skipDefaultBuilders = 0;
    // 生成get和getChecked校验函数，不过这些函数会使用到verify函数
    let genVerifyDecl = 1;
}

#endif // DIALECT_EXEC_IR_EXECTYPES_TD
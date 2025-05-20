#ifndef INCLUDE_DIALECT_EXEC_IR_EXECATTRS_TD
#define INCLUDE_DIALECT_EXEC_IR_EXECATTRS_TD
// 包括之前的文件
include "Dialect/Exec/IR/ExecDialect.td"
include "Dialect/Exec/IR/ExecTypes.td"
// 定义类型所需要的头文件
include "mlir/IR/AttrTypeBase.td"
// 定义属性基类 在对应的文件中，查看需要什么模板参数
class Exec_Attr<string name, string attrMnemonic, list<Trait> traits = [], string baseCppClass = "::mlir::Attribute">
    : AttrDef<Exec_Dialect, name, traits, baseCppClass>{
    // mnemonic 是助记符
    let mnemonic = attrMnemonic;
    string attrName = dialect.name # "." # attrMnemonic;
}
// 结构和Type的定义是类似的
def Exec_CIntAttr : Exec_Attr<"ExecCInt", "eCInt", []>{
    // 进行描述
    let summary = "this attr represent counts number of the same integer";
    let description = [{
        "Just for the next step to add or mul, represent the number of the same integer"
    }];
    // 输入参数
    let parameters = (ins
        "int64_t":$cnt
    );
    // 进行校验
    let genVerifyDecl = 1;
    let genStorageClass = 1;
    let skipDefaultBuilders = 0;
    let hasStorageCustomConstructor = 0;
    // let assemblyFormat = "`<` `cnts` `=`  $cnt `>`";
    let assemblyFormat = "`<` $cnt `>`";
    let builders = [
        AttrBuilder<(ins "int64_t":$cnt)>,
        AttrBuilder<(ins 
            "MLIRContext*":$ctx, 
            "int64_t":$cnt
        )>
    ];
}
#endif // INCLUDE_DIALECT_EXEC_IR_EXECATTRS_TD
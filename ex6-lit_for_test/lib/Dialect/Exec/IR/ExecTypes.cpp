#ifndef LIB_DIALECT_EXEC_IR_EXECDIALECTTYPES_CPP
#define LIB_DIALECT_EXEC_IR_EXECDIALECTTYPES_CPP
// 包括之前的头文件
#include "Dialect/Exec/IR/ExecDialect.h"
#include "Dialect/Exec/IR/ExecTypes.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/TypeSwitch.h"
#include "mlir/IR/BuiltinTypeInterfaces.h"
#include "mlir/IR/DialectImplementation.h"
#include "mlir/IR/OpImplementation.h"
#include "llvm/Support/LogicalResult.h"
#include "mlir/Support/LLVM.h"
#define FIX
#define GET_TYPEDEF_CLASSES
#include "Dialect/Exec/IR/ExecTypes.cpp.inc"
namespace mlir::exec{
    void ExecDialect::registerTypes(){
        llvm::outs() << "register " << getDialectNamespace() << " Type\n";
        addTypes<
            #define GET_TYPEDEF_LIST
            #include "Dialect/Exec/IR/ExecTypes.cpp.inc"
        >();
    }
    // 由于使用了genVerified，所以需要提供verify函数的实现
    LogicalResult ExecIntType::verify(function_ref<InFlightDiagnostic()> emitError, unsigned width, int64_t input){
        if(width != 8 && width != 16 && width != 32 && width != 64){
            return emitError() << "Invalid width! Only support for 8,16,32,64 \n"; 
        }
        return success();
    }
    // 自定义assenbleFormat
    // 返回解析的结果 像是解析，printer的内容
    Type ExecIntType::parse(AsmParser &parser) {
        // 返回Type() 就是在返回nullptr的内容 就代表解析失败了
        // 先解析 '<'
        if (parser.parseLess())
            return Type();

        // 解析固定字符串 "w:"
        if (parser.parseKeyword("w") || parser.parseColon())
            return Type();

        // 解析类型前缀 "i" + 宽度
        StringRef prefix;
        if (parser.parseKeyword(&prefix) || !prefix.starts_with("i"))
            return Type();

        unsigned width = 0;
        if (prefix.drop_front() // remove 'i'
                .getAsInteger(/*radix=*/10, width))
            return Type();

        // 解析 ':'
        if (parser.parseColon())
            return Type();

        // 解析 input 参数
        int64_t input = 0;
        if (parser.parseInteger(input))
            return Type();

        // 解析 '>'
        if (parser.parseGreater())
            return Type();

        return parser.getChecked<ExecIntType>(parser.getContext(), width, input);
    }

    // 就是输出
    void ExecIntType::print(AsmPrinter &printer) const {
        printer << "<w:";
        printer << "i" << getWidth() << ":";
        printer << getInput() << ">";
    }   
}
#undef FIX
#endif // LIB_DIALECT_EXEC_IR_EXECDIALECTTYPES_CPP
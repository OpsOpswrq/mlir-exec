// 接下来自定义类型
#ifndef INCLUDE_DIALECT_EXEC_IR_EXECDIALECTTYPES_H
#define INCLUDE_DIALECT_EXEC_IR_EXECDIALECTTYPES_H

#include "Dialect/Exec/IR/ExecDialect.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/MLIRContext.h"
#include "Dialect/Exec/IR/ExecTypes.h.inc"
#define FIX
#define GET_TYPEDEF_CLASSES
#include "Dialect/Exec/IR/ExecTypes.h.inc"
#undef FIX

#endif // INCLUDE_DIALECT_EXEC_IR_EXECDIALECTTYPES_H
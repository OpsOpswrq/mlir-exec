#ifndef INCLUDE_DIALECT_EXEC_IR_EXECATTRS_H
#define INCLUDE_DIALECT_EXEC_IR_EXECATTRS_H

#include "mlir/IR/BuiltinAttributeInterfaces.h"
#include "mlir/IR/AttributeSupport.h"
#include "Dialect/Exec/IR/ExecDialect.h"
#include "Dialect/Exec/IR/ExecTypes.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/MLIRContext.h"
#define GET_ATTRDEF_CLASSES
#include "Dialect/Exec/IR/ExecAttrs.h.inc"

#endif // INCLUDE_DIALECT_EXEC_IR_EXECATTRS_H
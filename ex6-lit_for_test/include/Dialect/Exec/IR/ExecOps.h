#ifndef INCLUDE_DIALECT_EXEC_IR_EXECOPS_H
#define INCLUDE_DIALECT_EXEC_IR_EXECOPS_H

#include "Dialect/Exec/IR/ExecAttrs.h"
#include "Dialect/Exec/IR/ExecDialect.h"
#include "Dialect/Exec/IR/ExecTypes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/OpImplementation.h"
#define FIX
#define GET_OP_CLASSES
#include "Dialect/Exec/IR/ExecOps.h.inc"
#undef FIX
#endif // INCLUDE_DIALECT_EXEC_IR_EXECOPS_H
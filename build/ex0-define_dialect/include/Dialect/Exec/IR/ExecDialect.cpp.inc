/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ExecDialect.td                                                       *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::exec::ExecDialect)
namespace mlir {
namespace exec {

ExecDialect::ExecDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<ExecDialect>())
    
     {
  getContext()->loadDialect<arith::ArithDialect>();
  initialize();
}
} // namespace exec
} // namespace mlir

/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: ExecDialect.td                                                       *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {
namespace exec {

class ExecDialect : public ::mlir::Dialect {
  explicit ExecDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~ExecDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("Exec_Dialect");
  }

        void sayHello(llvm::StringRef name);
    };
} // namespace exec
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::exec::ExecDialect)

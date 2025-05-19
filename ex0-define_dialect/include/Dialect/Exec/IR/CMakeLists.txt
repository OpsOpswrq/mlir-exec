# 添加mlir-tablegen的内容
# 首先添加mlir-tablegen的对象是基于哪个文件的
set(LLVM_TARGET_DEFINITIONS ExecDialect.td)
# 添加对应生成的东西
mlir_tablegen(ExecDialect.h.inc --gen-dialect-decls -dialect=Exec_Dialect)
mlir_tablegen(ExecDialect.cpp.inc --gen-dialect-defs -dialect=Exec_Dialect)
# 添加这些生成内容为公共文件，这些内容可以作为文件依赖来进行操作
add_public_tablegen_target(ExecDialectInGen${EXEC})
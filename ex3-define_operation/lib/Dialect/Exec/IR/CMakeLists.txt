add_mlir_dialect_library(MLIRExecDialect${EXEC}
    ExecDialect.cpp
    ExecTypes.cpp
    ExecAttrs.cpp
    ExecOps.cpp

    DEPENDS
    ExecDialectInGen${EXEC}

    LINK_LIBS
    PUBLIC MLIRIR
    PUBLIC LLVMSupport
    PUBLIC MLIRParser
    PUBLIC MLIRArithDialect
    PUBLIC MLIRSCFDialect
    PUBLIC MLIRSupport
    PUBLIC MLIRFuncDialect
)
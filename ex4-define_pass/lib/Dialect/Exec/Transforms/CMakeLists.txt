add_mlir_dialect_library(MLIRExecDialectTransform${EXEC}
    Passes.cpp

    DEPENDS
    ExecDialectPassesInGen${EXEC}

    LINK_LIBS
    PUBLIC MLIRExecDialect${EXEC}
)
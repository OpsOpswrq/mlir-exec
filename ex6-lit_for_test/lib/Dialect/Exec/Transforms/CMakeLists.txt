add_mlir_dialect_library(MLIRExecDialectTransform${EXEC}
    ApplyRewritePattern.cpp

    DEPENDS
    ExecDialectPassesInGen${EXEC}

    LINK_LIBS
    PUBLIC MLIRExecDialect${EXEC}
    PUBLIC MLIRPass
    PUBLIC MLIRTransforms
    PUBLIC MLIRTransformUtils
)
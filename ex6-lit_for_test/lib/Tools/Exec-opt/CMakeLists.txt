# 结构可以在对应MLIR Tools mlir-opt文件夹中看到
set(LIBS
  ${all_libs}
  ${dialect_libs}
  ${conversion_libs}
  ${extension_libs}
  ${translation_libs}

  MLIRAffineAnalysis
  MLIRAnalysis
  MLIRCastInterfaces
  MLIRDialect
  MLIROptLib
  MLIRParser
  MLIRPass
  MLIRTransforms
  MLIRTransformUtils
  MLIRSupport
  MLIRIR

  # TODO: Remove when registerAllGPUToLLVMIRTranslations is no longer
  # registered directly in mlir-opt.cpp.
  MLIRToLLVMIRTranslationRegistration
  MLIRExecDialectTransform${EXEC}
  MLIRExecDialect${EXEC}
  )

add_mlir_tool(Exec-opt${EXEC}
  Exec-opt.cpp

  DEPENDS
  ${LIBS}
)
target_link_libraries(Exec-opt${EXEC} PRIVATE ${LIBS})
llvm_update_compile_flags(Exec-opt${EXEC})

mlir_check_all_link_libraries(Exec-opt${EXEC})
export_executable_symbols_for_plugins(Exec-opt${EXEC})
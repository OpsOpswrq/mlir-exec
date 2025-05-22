# 配置lit套件设置
configure_lit_site_cfg(
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
  MAIN_CONFIG
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
)
# 工具依赖
set(TEST_DEPENDS
  FileCheck count not
  Exec-opt${EXEC}
)

add_lit_testsuite(check-ch-${EXEC} "Running the lit regression tests..."
  ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${TEST_DEPENDS}
)
set_target_properties(check-ch-${EXEC} PROPERTIES FOLDER "test")


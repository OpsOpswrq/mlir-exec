// RUN: exec-opt %s --apply-pass-in-exec | FileCheck %s

module {
  func.func @test_add(%arg0: !Exec_Dialect.eInt<w:i16:16>, %arg1: !Exec_Dialect.eInt<w:i16:16>) -> !Exec_Dialect.eInt<w:i16:16> {
    %0 = "Exec_Dialect.ExecAdd"(%arg0, %arg1) <{cnt = #Exec_Dialect.eCInt<2>}> : (!Exec_Dialect.eInt<w:i16:16>, !Exec_Dialect.eInt<w:i16:16>) -> !Exec_Dialect.eInt<w:i16:16>
    return %0 : !Exec_Dialect.eInt<w:i16:16>
  }
}

// CHECK-LABEL: func.func @test_add
// CHECK-SAME: (%[[ARG0:.*]]: !Exec_Dialect.eInt<w:i16:16>, %[[ARG1:.*]]: !Exec_Dialect.eInt<w:i16:16>) -> !Exec_Dialect.eInt<w:i16:16>
// CHECK: %[[CONST:.*]] = arith.constant 64 : i16
// CHECK: %[[RESULT:.*]] = "Exec_Dialect.wrap"(%[[CONST]]) : (i16) -> !Exec_Dialect.eInt<w:i16:16>
// CHECK: return %[[RESULT]] : !Exec_Dialect.eInt<w:i16:16>
// CHECK-NOT: Exec_Dialect.ExecAdd
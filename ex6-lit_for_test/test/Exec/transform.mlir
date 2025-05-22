// RUN: exec-opt %s --apply-pass-in-exec > %t
// RUN: FileCheck %s < %t

module {
  func.func @test_add(%arg0: !Exec_Dialect.eInt<w:i16:16>, %arg1: !Exec_Dialect.eInt<w:i16:16>) -> !Exec_Dialect.eInt<w:i16:16> {
    %c64_i16 = arith.constant 64 : i16
    %0 = "Exec_Dialect.wrap"(%c64_i16) : (i16) -> !Exec_Dialect.eInt<w:i16:16>
    return %0 : !Exec_Dialect.eInt<w:i16:16>
  }
}

// 本质还是一个文件 可以写注释的
// CHECK-LABEL: func.func @test_add
// CHECK-SAME: (%[[ARG0:.*]]: !Exec_Dialect.eInt<w:i16:16>, %[[ARG1:.*]]: !Exec_Dialect.eInt<w:i16:16>) -> !Exec_Dialect.eInt<w:i16:16>
// CHECK: %[[CONST:.*]] = arith.constant 64 : i16
// CHECK: %[[RESULT:.*]] = "Exec_Dialect.wrap"(%[[CONST]]) : (i16) -> !Exec_Dialect.eInt<w:i16:16>
// CHECK: return %[[RESULT]] : !Exec_Dialect.eInt<w:i16:16>
// CHECK-NOT: Exec_Dialect.ExecAdd
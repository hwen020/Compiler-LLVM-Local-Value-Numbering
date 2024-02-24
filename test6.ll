; ModuleID = 'test6.c'
source_filename = "test6.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @test6(i32 noundef %c, i32 noundef %d, i32 noundef %e, i32 noundef %i, i32 noundef %j) #0 {
entry:
  %c.addr = alloca i32, align 4
  %d.addr = alloca i32, align 4
  %e.addr = alloca i32, align 4
  %i.addr = alloca i32, align 4
  %j.addr = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %t1 = alloca i32, align 4
  %t2 = alloca i32, align 4
  %t3 = alloca i32, align 4
  %t4 = alloca i32, align 4
  store i32 %c, i32* %c.addr, align 4
  store i32 %d, i32* %d.addr, align 4
  store i32 %e, i32* %e.addr, align 4
  store i32 %i, i32* %i.addr, align 4
  store i32 %j, i32* %j.addr, align 4
  store i32 10, i32* %a, align 4
  store i32 40, i32* %b, align 4
  %0 = load i32, i32* %i.addr, align 4
  %1 = load i32, i32* %j.addr, align 4
  %mul = mul nsw i32 %0, %1
  store i32 %mul, i32* %t1, align 4
  %2 = load i32, i32* %t1, align 4
  %add = add nsw i32 %2, 40
  store i32 %add, i32* %c.addr, align 4
  store i32 150, i32* %t2, align 4
  %3 = load i32, i32* %c.addr, align 4
  %mul1 = mul nsw i32 150, %3
  store i32 %mul1, i32* %d.addr, align 4
  %4 = load i32, i32* %i.addr, align 4
  store i32 %4, i32* %e.addr, align 4
  %5 = load i32, i32* %i.addr, align 4
  %6 = load i32, i32* %j.addr, align 4
  %mul2 = mul nsw i32 %5, %6
  store i32 %mul2, i32* %t3, align 4
  %7 = load i32, i32* %i.addr, align 4
  %mul3 = mul nsw i32 %7, 10
  store i32 %mul3, i32* %t4, align 4
  %8 = load i32, i32* %t1, align 4
  %9 = load i32, i32* %t4, align 4
  %add4 = add nsw i32 %8, %9
  store i32 %add4, i32* %c.addr, align 4
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}

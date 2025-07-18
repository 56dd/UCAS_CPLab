; ModuleID = './29.cact'
source_filename = "./29.cact"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = dso_local global i32 -1, align 4
@b = dso_local global i32 1, align 4

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z5inc_av() #0 {
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  %2 = load i32, ptr @a, align 4
  store i32 %2, ptr %1, align 4
  %3 = load i32, ptr %1, align 4
  %4 = add nsw i32 %3, 1
  store i32 %4, ptr %1, align 4
  %5 = load i32, ptr %1, align 4
  store i32 %5, ptr @a, align 4
  %6 = load i32, ptr @a, align 4
  ret i32 %6
}

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #1 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 5, ptr %2, align 4
  br label %3

3:                                                ; preds = %37, %0
  %4 = load i32, ptr %2, align 4
  %5 = icmp sge i32 %4, 0
  br i1 %5, label %6, label %40

6:                                                ; preds = %3
  %7 = call noundef i32 @_Z5inc_av()
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %9, label %19

9:                                                ; preds = %6
  %10 = call noundef i32 @_Z5inc_av()
  %11 = icmp ne i32 %10, 0
  br i1 %11, label %12, label %19

12:                                               ; preds = %9
  %13 = call noundef i32 @_Z5inc_av()
  %14 = icmp ne i32 %13, 0
  br i1 %14, label %15, label %19

15:                                               ; preds = %12
  %16 = load i32, ptr @a, align 4
  %17 = load i32, ptr @b, align 4
  %18 = add nsw i32 %16, %17
  store i32 %18, ptr @a, align 4
  br label %19

19:                                               ; preds = %15, %12, %9, %6
  %20 = call noundef i32 @_Z5inc_av()
  %21 = icmp slt i32 %20, 14
  br i1 %21, label %31, label %22

22:                                               ; preds = %19
  %23 = call noundef i32 @_Z5inc_av()
  %24 = icmp ne i32 %23, 0
  br i1 %24, label %25, label %35

25:                                               ; preds = %22
  %26 = call noundef i32 @_Z5inc_av()
  %27 = call noundef i32 @_Z5inc_av()
  %28 = sub nsw i32 %26, %27
  %29 = add nsw i32 %28, 1
  %30 = icmp ne i32 %29, 0
  br i1 %30, label %31, label %35

31:                                               ; preds = %25, %19
  %32 = load i32, ptr @b, align 4
  store i32 %32, ptr @a, align 4
  %33 = load i32, ptr @b, align 4
  %34 = mul nsw i32 %33, 2
  store i32 %34, ptr @b, align 4
  br label %37

35:                                               ; preds = %25, %22
  %36 = call noundef i32 @_Z5inc_av()
  br label %37

37:                                               ; preds = %35, %31
  %38 = load i32, ptr %2, align 4
  %39 = sub nsw i32 %38, 1
  store i32 %39, ptr %2, align 4
  br label %3, !llvm.loop !6

40:                                               ; preds = %3
  %41 = load i32, ptr @a, align 4
  %42 = load i32, ptr @b, align 4
  %43 = add nsw i32 %41, %42
  ret i32 %43
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 17.0.6 (++20231209124227+6009708b4367-1~exp1~20231209124336.77)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}

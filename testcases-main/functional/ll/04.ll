; ModuleID = './04.cact'
source_filename = "./04.cact"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@__const.main.c = private unnamed_addr constant [4 x [2 x i32]] [[2 x i32] [i32 1, i32 2], [2 x i32] [i32 3, i32 4], [2 x i32] [i32 5, i32 6], [2 x i32] [i32 7, i32 8]], align 16
@__const.main.e = private unnamed_addr constant [4 x [2 x i32]] [[2 x i32] [i32 1, i32 2], [2 x i32] [i32 3, i32 4], [2 x i32] [i32 5, i32 6], [2 x i32] [i32 7, i32 8]], align 16

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [4 x [2 x i32]], align 16
  %3 = alloca [4 x [2 x i32]], align 16
  %4 = alloca [4 x [2 x i32]], align 16
  store i32 0, ptr %1, align 4
  call void @llvm.memset.p0.i64(ptr align 16 %2, i8 0, i64 32, i1 false)
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %3, ptr align 16 @__const.main.c, i64 32, i1 false)
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %4, ptr align 16 @__const.main.e, i64 32, i1 false)
  %5 = getelementptr inbounds [4 x [2 x i32]], ptr %3, i64 0, i64 2
  %6 = getelementptr inbounds [2 x i32], ptr %5, i64 0, i64 1
  %7 = load i32, ptr %6, align 4
  %8 = getelementptr inbounds [4 x [2 x i32]], ptr %4, i64 0, i64 0
  %9 = getelementptr inbounds [2 x i32], ptr %8, i64 0, i64 0
  store i32 %7, ptr %9, align 16
  %10 = getelementptr inbounds [4 x [2 x i32]], ptr %3, i64 0, i64 1
  %11 = getelementptr inbounds [2 x i32], ptr %10, i64 0, i64 1
  %12 = load i32, ptr %11, align 4
  %13 = getelementptr inbounds [4 x [2 x i32]], ptr %4, i64 0, i64 0
  %14 = getelementptr inbounds [2 x i32], ptr %13, i64 0, i64 1
  store i32 %12, ptr %14, align 4
  %15 = getelementptr inbounds [4 x [2 x i32]], ptr %4, i64 0, i64 3
  %16 = getelementptr inbounds [2 x i32], ptr %15, i64 0, i64 1
  %17 = load i32, ptr %16, align 4
  %18 = getelementptr inbounds [4 x [2 x i32]], ptr %4, i64 0, i64 0
  %19 = getelementptr inbounds [2 x i32], ptr %18, i64 0, i64 0
  %20 = load i32, ptr %19, align 16
  %21 = add nsw i32 %17, %20
  %22 = getelementptr inbounds [4 x [2 x i32]], ptr %4, i64 0, i64 0
  %23 = getelementptr inbounds [2 x i32], ptr %22, i64 0, i64 1
  %24 = load i32, ptr %23, align 4
  %25 = add nsw i32 %21, %24
  %26 = getelementptr inbounds [4 x [2 x i32]], ptr %2, i64 0, i64 2
  %27 = getelementptr inbounds [2 x i32], ptr %26, i64 0, i64 0
  %28 = load i32, ptr %27, align 16
  %29 = add nsw i32 %25, %28
  ret i32 %29
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #1

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #2

attributes #0 = { mustprogress noinline norecurse nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #2 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 17.0.6 (++20231209124227+6009708b4367-1~exp1~20231209124336.77)"}

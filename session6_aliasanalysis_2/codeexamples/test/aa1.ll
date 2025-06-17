; ModuleID = 'test/aa1.c'
source_filename = "test/aa1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind
define dso_local void @foo() #0 {
entry:
  %a = alloca i32, align 4
  store i32 0, ptr %a, align 4
  call void @bar(ptr noundef %a)
  ret void
}

declare void @bar(ptr noundef) #1

attributes #0 = { noinline nounwind "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" }
attributes #1 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 20.1.0 (https://github.com/llvm/llvm-project.git 24a30daaa559829ad079f2ff7f73eb4e18095f88)"}

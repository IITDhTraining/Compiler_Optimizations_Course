define i32 @test(i32 %a, i32 %b, i1 %cond) {
entry:
  %x = alloca i32
  br i1 %cond, label %then, label %else

then:
  store i32 %a, i32* %x
  br label %merge

else:
  store i32 %b, i32* %x
  br label %merge

merge:
  %val = load i32, i32* %x
  ret i32 %val
}

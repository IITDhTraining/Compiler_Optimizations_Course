define i32 @foo(i32 %v) {
  %lo = trunc i32 %v to i16
  %p = add i16 %lo, 5
  %c = icmp ugt i16 %p, 6
  %r = select i1 %c, i32 %v, i32 9
  ret i32 %r
}
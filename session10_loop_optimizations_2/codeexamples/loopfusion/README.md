# Loop_Fusion with LLVM's built in pass, loop-fusion, for fusing loops
- `make run` produces unoptimized LLVM IR for a sample program, `loopfusion.c`, translates this to optimized version using the `mem2reg` pass, then chains a sequence of optimizations (including `loop-fusion`) and passes them to the `opt` pass pipeline to produce the IR with fused loops in `loop_fused.ll`.

Also, `.png` files for CFG corresponding to unoptimized and fused LLVM IR are produced.

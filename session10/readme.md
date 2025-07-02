# (Optimizing Transformations)

This directory contains slides and code demos on loop optimizations. In particular, on loop unrolling and loop vectorization. 

## I. Installing `llvm`

```
git clone https://github.com/llvm/llvm-project.git
git checkout tags/llvmorg-20.1.0
```

Building with cmake:
```
mkdir llvm-project/build
cd llvm-project
cmake -S llvm -B build -G Ninja \
   -DLLVM_ENABLE_PROJECTS=llvm;clang;clang-tools-extra;lldb;lld \
   -DLLVM_BUILD_EXAMPLES=ON \
   -DLLVM_TARGETS_TO_BUILD="Native;NVPTX;AMDGPU" \
   -DCMAKE_BUILD_TYPE=Debug \
   -DLLVM_ENABLE_ASSERTIONS=ON \
   -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_ENABLE_LLD=ON
ninja -C -build . 
```
If you have the `llvm-project` created other than in the home drive, you need to modify `setenv.sh` to tell the `PATH` variable to find the newly built compiler in the specific location. 

execute the command `source setenv.sh`


## II. Examples (in codeexample directory)
- `make looppeel`. To see that few iterations of a loop are moved before the loop to eliminate phi nodes. Observe the absence of phi nodes in the CFGs generated after (`looppeel_after_peeling.png`) and after(`looppeel_before_peeling.png`) the transformation. `looppeel.c` is the sample program considered and it is expected that after 4 iterations only the phi node corresponding to induction variable i remains (phi nodes for `x`, `y`, `a` are all eliminated). 

**exercise**: change `x=y` in `looppeel.c` to `x=y+1`. Why does'nt the phi node get eliminated?

- `make looppeel2`. This is another example for loop peeling, where the if condition is eliminated. `looppeel2.c` is considered as the program on which transformation is done. You can see in `looppeel2_after_peeling.png` that the `if` block gets eliminated from the loop body and the corresponding block gets moved before the loop. 

- `make unroll1`. To see how inlining of a function allows for unrolling a loop and that (force) unrolling before inlining may miss opportunities and may even lead to incorrect results. To inline the function in `unroll1.c`, follow the instruction mentioned in comment. 

- `make unroll2`. To see how runtime unrolling is done and an unroll factor is specified. The program `unroll2.c` is considered and 4 iterations of the loop are unrolled. 

- Goto the LICM directory and follow the instructions in the README. This shows how to write a module pass that does LICM. 

- Goto loopfusion directory and follow the instructions in the README. This shows how to use the available `loop-fusion` pass to perform loop-fusion.

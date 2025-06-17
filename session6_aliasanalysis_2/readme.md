# (Alias Analysis)

This directory contains slides on Alias Analysis implementations in LLVM and codeexamples.

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
First you need to build the pass (i.e. your library) implementing alias analysis. This is implemented as analysis passes in LLVM. Upon successful build, `aa.so` is created in `aa/build` directory.

1. To build the library, execute `make testbuild` 

2. `make runaa` - after building the library, executing this command creates a .ll file for a default test program, `test/aa1.c` and then runs the alias analysis on the .ll file created in the `test` directory.
 
3. You can change the test program and the alias query to use `alias` or `getModRefInfo` methods by editing the `TESTFLAG` in the `Makefile`.

Acknowledgements:
The exercise problem is from LLVM Social's [Heuristics for stateful flow-sensitive alias analysis in LLVM](https://www.youtube.com/watch?v=uU4ozaNuOYM)

References:
https://llvm.org/docs/AliasAnalysis.html
[Type-based alias analysis](https://dl.acm.org/doi/10.1145/277652.277670)

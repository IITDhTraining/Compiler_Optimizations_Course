# (Liveness Analysis, Reaching Definitions) with LLVM

This repository contains examples that use LLVM toolchain and framework to do liveness and reaching definitions analysis.

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

## II. Examples
First you need to build the libraries corresponding liveness analysis and reaching definitions. These libraries are implemented as analysis passes in LLVM. Upon successful build, `liveness.so` and `reachingdefs.so` are created.
To build these libraries e.g., `liveness.so`, the following steps:

```
cd liveness
mkdir build
cd build
cmake ..
make
```

repeat the above (change `liveness` to `reachingdefs`) to build `reachingdefs.so` in the `reachingdefs` directory.
 

1. **Running reaching defs analysis**
 
  `make reachingdefs` - This command by default, runs a reaching definitions analysis on `example4.c` present in the `test` directory. 
 
2. **Running liveness analysis**
 
 `make liveness` - This command by default, runs a liveness analysis on `example4.c` present in the `test` directory. 


## III. Exercise
How do you print all instructions whose results are not used anywhere? (i.e. instructions that have no uses?)

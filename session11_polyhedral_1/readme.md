# (Polyhedral Compilation - 1)

This directory contains slides and code demos on Polyhedral Compilation. The only code example shared allows you to visualize SCoPs and regions.

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
   -DLLVM_ENABLE_PROJECTS="llvm;clang;clang-tools-extra;lldb;lld;polly" \
   -DLLVM_BUILD_EXAMPLES=ON \
   -DLLVM_TARGETS_TO_BUILD="Native;NVPTX;AMDGPU" \
   -DCMAKE_BUILD_TYPE=Release \
   -DLLVM_ENABLE_ASSERTIONS=ON \
   -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
ninja -C build . 
```
Note that in the above, you need to enable `polly` in the list of projects that you wish to build. The above command assumes that there is already gcc toolchain and Ninja available. 


After successful build, edit `setenv.sh` and execute `source setenv.sh` to point to your newly built Clang compiler.


## II. Examples (in codeexample directory)
- `make test_scop_polly`. To see (on terminal) that SCoPs are identified and an analysis that tells you whether it is a valid SCoP or not. 

**exercise**: uncomment the line in the `Makefile` and generate a .png file to visualize. In the .png file generated, how many regions do you see? 

**exercise**: why is the SCoP analysis telling you that it is an invalid SCoP (as printed on the terminal) for the `test_scop.c` program?

# (Optimizing Transformations)

This directory contains slides on Transformations and codeexamples (on pass plugin and InstCombine) that show how to rewrite IR in a transformation pass.  

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
1. llvm transformation pass 

- `make build` builds the transformation pass plugin from scratch. A `mypass.so` file is created. This `mypass.so` file can be used with `clang` or `opt` (depending upon static-time or link-time) to run the pass.

- `make run` does a static-time linking of the `mypass.so` to run the pass, which replaces a multiplication with addition in a default program, `binaryop.c`, in `test` folder.


- To test the link-time usage of `mypass.so`, execute `make debug` to generate `mypass.so`, run the transformation on `binaryop.c`.

you can compare the differences of files `binaryop_before.ll` and `binaryop_transformed.ll` to see the rewriting of `add` and `sub` instructions with `mul` instructions. Also notice that the `add` and `sub` instructions have been removed.

2. InstCombine: peephole optimizations with llvm
- Make changes in the `visitAddSub` method of `InstCombineAddSub.cpp` file in `llvm/lib/Transforms/InstCombine`. E.g.,
```
Value *A, *B;
  if((match(LHS, m_Value(A))) && (match(RHS, m_Value(B))))
     return BinaryOperator::CreateMul(A, B);
```
before the comment: 
```
// X + X --> X << 1
```

you are trying to replace a binary operation with Multiply with above changes.  For a sample .ll file
```
define i32 @foo(i32 %x) {
  %y = add i32 %x, %x
  ret i32 %y
}
```

you would see the output as:
```
define i32 @foo(i32 %x) {
  %y = mul i32 %x, %x
  ret i32 %y
}
```

when you execute the command `opt -passes=instcombine instcombineex.ll -S` 



References:
[LLVM for Grad Students](https://www.cs.cornell.edu/~asampson/blog/llvm.html)

# (Control Flow Graphs, Dominators, Dominator Trees, Dominance Frontier, SSA form) with LLVM

This repository contains examples that use LLVM toolchain and framework to print control flow graphs for a program, dominator relationship between basic blocks in a program, dominator tree, dominance frontier of a basic block, and how the optimized SSA form is generated.

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
You can change the input program for all examples by modifying line 1 of the `makefile`.

1. **Printing Control Flow Graph**
   `make cfg` - By default generates a `example2.png` file in the `test` directory. 
 
2. **Printing dominators**
   A pass `MyPass.so` needs to be created first. The source code and scaffolding for all this is present in the `fnmodpass` directory. To create `MyPass.so`:

    ```
    cd fnmodpass;mkdir build;cd build;cmake ..;make
    ```

    Now use the `.so` created with LLVM's opt. change directory to `codeexamples` and type `make dominators`. 


    The `make dominator` has the below command in the recipe:
 
    ```
    opt -load-pass-plugin=./fnmodpass/build/MyPass.so -passes="my-module-pass" -disable-output  $(TESTCASE).bc`
    ```
    This is the preferred method of loading passes (other method is to use `clang -fpass-plugin=<path-to-.so> <input.bc>`)

    A good starting point to learn about passes is Adrian Sampson's [LLVM for Grad Students](https://www.cs.cornell.edu/~asampson/blog/llvm.html).

    The `make dominators` command prints (on the terminal) the dominator relationship between each pair of basic blocks in a CFG.

3. **Printing Dominator Trees**

    `make domtree` - if your input program does not have a main function (assuming that you have modified line 1 of the `makefile` then this may not produce the expected `.png` file. You need to change the `dot -Tpng dom.main.dot -o $(TESTCASE)_dom.png` command in the recipe to make it work. By default, this command generates the file `example2_dom.png` in the `test` directory.
    
4. **Printing Dominance Frontier**

    `make domfrontier` - Before executing this command, you need to uncomment certain code in `passes.cpp` in the `fnmodpass` directory, enter the `build` directory within and (re)create the `MyPass.so` file. 

5. **Using *mem2reg* pass**

   execute the command: `opt -passes=mem2reg example3.ll -S -o example3_mem2reg.ll`

   The above command uses the `mem2reg` pass to get rid of `alloca`- stack allocated variables to optimize the IR and insert a phi node.


## III. Exercise
Try II.1, II.2, II.3, and II.4 with input program `example4.c` provided in the `test` directory.

# (Code Generation - 3)

This directory contains slides and code demos on codegenration using GlobalISel. The demo examples are executed using each of the targets specified in the `Makefile`. 

## I. Installing `llvm`

```
git clone https://github.com/llvm/llvm-project.git
git checkout tags/llvmorg-20.1.0
```

Building with cmake and Ninja:
- see `build_command.txt`
- After successful build, edit `setenv.sh` and execute `source setenv.sh` to point to your newly built Clang compiler.



## II. Examples (in codeexample directory)
- `make gMIR`. This creates generic MIR after the ir translation pass. The output is stored in `test.gmir` file.
- `make legalize`. This legalizes the generic MIR from `test.gmir` produced earlier. Creates generic MIR and the output is stored in `test.gmir` file.
- `make selectreg`. This creates generic MIR after selecting reg banks. Notice the change in constraints on the virtual registers in `test.selectreg` file.
- `make isel`. This selects instructions and produces machine instructions closer to target. Notice the absence of generic opcodes, virtual registers. The output is stored in `test.isel` file.


**exercise**: `SelectionDAG operates on basic-block and may loose global optimization opportunities. GlobalISel operates at the function level.`. With the help of a suitable example .c/.ll file, show proof of this statement.  



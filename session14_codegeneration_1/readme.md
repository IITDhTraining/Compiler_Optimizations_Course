# (Code Generation - 1)

This directory contains slides and code demos on code generation with LLVM. The SelectionDAG code generator module is used and the demo examples are executed using each of the targets specified in the `Makefile`. 

## I. Installing `llvm`

see `build_command.txt`

After successful build, edit `setenv.sh` and execute `source setenv.sh` to point to your newly built Clang compiler.


## II. Examples 
For each of the target specified in the makefile execute `make <targetname>`. Observe the changes (if any) in the .png file generated corresponding to the target. E.g.,

- observe changes in the `.png` files generated (`test.png` and `optimize1.png`) when you do `make optimize1`
- execute `make legalizetype` and inspect `iseldump.txt`, which records the activity of the SelectionDAG for each of the phases discussed. 

**exercise**: use `testlegalize.c` with the `Makefile` to see *expansion* during type legalization discussed in class.

**exercise**: write a `.c` file, which when used with targets `legalizeops` and `optimize1` mentioned in the makefile,  shows differences in `optimize1.png` and `legalizeops.png` that correspond to DAG before and after (resp.) legalizing operations and types.


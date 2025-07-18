
noscop:  noscop.c 
	clang -O3 -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt -polly-canonicalize -dot-scops -disable-output $@.ll 
	dot -Tpng scops.foo.dot -o $@.png
	opt -polly-print-detect -disable-output $@.ll 

invalidregion:  invalidregion.c
	clang -O1 -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt -polly-canonicalize -dot-scops -disable-output $@.ll 
	dot -Tpng scops.foo.dot -o $@.png
	opt -polly-print-detect -disable-output $@.ll 

profitablescop:  profitablescop.c
	clang -O1 -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt -polly-canonicalize -dot-scops -disable-output $@.ll 
	dot -Tpng scops.foo.dot -o $@.png
	opt -polly-print-detect -disable-output $@.ll 

analysis: rpassanalysis.c
	clang -O3 -mllvm -polly -Rpass-analysis=polly $<

missed: rpassmissed.c
	clang -O3 -mllvm -polly -Rpass-missed=polly $<

#demo to show polyhedral representation
scoprep: rpassanalysis.c
	clang -O1 -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt -polly-scops -debug-only=polly-scops -disable-output $@.ll
#exercise: a) change this to -O0 above. Why don't you see any details?
# b) while keeping at -O0, how can you get opt to output the details?
#	opt -passes=dot-cfg -cfg-dot-filename-prefix=$@ $@.ll
#	dot -Tpng $@.foo.dot -o $@.png 

#demo to show loop optimization with polly
matmul: matmul.c
#	clang -O3 -mllvm -polly -mllvm -polly-parallel-force -fopenmp -mllvm -polly-num-threads=16 $< -o $@_polly_parallel
	clang -O3 $< -o $@_plain
	clang -O3 -mllvm -polly $< -o $@_polly

#highlighting SCoPs on CFG
matmul_showscops: matmul.c
	clang -O3 -mllvm -polly -Rpass-analysis=polly $<
	clang -O1 -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt -polly-canonicalize -dot-scops-only -disable-output $@.ll -polly-use-llvm-names
	dot -Tpng scopsonly.main.dot -o $@_main.png
	dot -Tpng scopsonly.init_array.dot -o $@_initarray.png
	dot -Tpng scopsonly.print_array.dot -o $@_printarray.png
#exercise: fire this rule and explain why you don't see a highlighted SCoP in matmul_initarray.png and matmul_printarray.png

#demo to show exporting polyhedral representation to a file
matmul_ex: matmul.c
	clang -S -emit-llvm matmul.c -Xclang -disable-O0-optnone -o matmul.ll
	opt -S -polly-canonicalize matmul.ll -o matmul.preopt.ll
	opt -basic-aa -polly-export-jscop matmul.preopt.ll -polly-process-unprofitable -disable-output -polly-use-llvm-names

#demo to show importing a file containing transformed polyhedral representation i.e., modified schedule, corresponding to loop interchange
matmul_import_interchange: matmul.c
	clang -S -emit-llvm matmul.c -Xclang -disable-O0-optnone -o matmul.ll
	opt -S -polly-canonicalize matmul.ll -o matmul.preopt.ll
	opt -basic-aa -polly-import-jscop -polly-ast matmul.preopt.ll -polly-import-jscop-postfix=interchanged -polly-process-unprofitable -polly-use-llvm-names

#demo to show generation of code (IR) based on modified schedule
matmul_codegen_interchange: matmul.preopt.ll
	opt -S -basic-aa -polly-import-jscop -polly-import-jscop-postfix=interchanged -polly-codegen -polly-process-unprofitable -polly-use-llvm-names matmul.preopt.ll | opt -O3 -S -o matmul.polly.interchanged.ll

#demo to show generation of target
matmul_polly_interchange: matmul.polly.interchanged.ll
	llc matmul.polly.interchanged.ll -filetype=obj -o matmul_polly.interchanged.o -relocation-model=pic
	clang matmul_polly.interchanged.o -o matmul_polly_interchanged

#demo to show comparison of execution times (ijk vs. ikj)
#demo to show generation of target
matmul_compare: matmul.preopt.ll
	llc matmul.preopt.ll -filetype=obj -o matmul.plain.o -relocation-model=pic
	clang matmul.plain.o -o matmul_plain 

clean:
	rm -f matmul_plain matmul_polly matmul_polly_parallel matmul_polly_interchanged *.png *.ll *.dot *.o

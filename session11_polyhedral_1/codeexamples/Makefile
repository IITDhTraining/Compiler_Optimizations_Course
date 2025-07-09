
all:test_scop 

test_scop_polly: test_scop.c
	clang -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt --polly-print-scops $@.ll -o $@
	opt -passes=dot-cfg -cfg-dot-filename-prefix=$@ $@.ll
	dot -Tpng $@.foo.dot -o $@.png
#	clang -O3 -mllvm -polly -mllvm -polly-show -emit-llvm -S $< -o $@.ll
clean:
	rm -f test_scop_polly *.png *.ll *.dot 

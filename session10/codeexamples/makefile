#loop unrolling: peeling to remove the first few iterations of a loop and discover ivariants
looppeel: test/looppeel.c
	clang -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt -passes=mem2reg -S $@.ll -o $@.ll.promoted
	opt -passes=dot-cfg -cfg-dot-filename-prefix=$@ $@.ll.promoted
	dot -Tpng $@.foo.dot -o $@_before_peeling.png
	opt -passes=loop-unroll $@.ll.promoted -S -o $@.output
	opt -passes=dot-cfg -cfg-dot-filename-prefix=$@ $@.output
	dot -Tpng $@.foo.dot -o $@_after_peeling.png

looppeel2: test/looppeel2.c
	clang -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt -passes=mem2reg -S $@.ll -o $@.ll.promoted
	opt -passes=dot-cfg -cfg-dot-filename-prefix=$@ $@.ll.promoted
	dot -Tpng $@.main.dot -o $@_before_peeling.png
	opt -passes=loop-unroll $@.ll.promoted -S -o $@.output
	opt -passes=dot-cfg -cfg-dot-filename-prefix=$@ $@.output
	dot -Tpng $@.main.dot -o $@_after_peeling.png

unroll1: test/unroll1.c
	clang -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt -passes=mem2reg -S $@.ll -o $@.ll.promoted
	opt -passes=loop-unroll-full $@.ll.promoted -S -o $@.output 

#runtime unrolling:apply the loop-unroll pass and specify an unroll count
#generate the CFG before and after unrolling
unroll2: test/unroll2.c
	clang -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	opt -passes=dot-cfg -cfg-dot-filename-prefix=$@ $@.ll
	dot -Tpng $@.foo.dot -o $@_before_unrolling.png
	opt -passes=loop-unroll -unroll-runtime -unroll-count=4 $@.ll -S -o $@.output
	opt -passes=dot-cfg -cfg-dot-filename-prefix=$@ $@.output
	dot -Tpng $@.foo.dot -o $@_after_unrolling.png 
	
clean:
	rm -rf *.ll *.output *.promoted *.png *.dot

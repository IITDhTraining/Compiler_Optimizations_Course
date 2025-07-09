run:
	clang -O1 -Xclang -disable-O0-optnone -S -emit-llvm ../test/loopfusion.c -o ../test/loopfusion.ll
	opt -passes=mem2reg -S ../test/loopfusion.ll -o ../test/loopfusion_mem2reg.ll
	opt -passes='function(loop-simplify,lcssa,indvars,loop-fusion)' -S ../test/loopfusion_mem2reg.ll -o ../test/loopfused.ll
	opt -passes=dot-cfg -cfg-dot-filename-prefix=loopfusion ../test/loopfusion.ll
	dot -Tpng loopfusion.main.dot -o ../test/loop_before_fusion.png
	opt -passes=dot-cfg -cfg-dot-filename-prefix=loopfusion ../test/loopfused.ll
	dot -Tpng loopfusion.main.dot -o ../test/loop_after_fusion.png

clean:
	rm -f ../test/loopfusion*.ll ../test/loopfused.ll
	rm -f ../test/loop*fusion.png

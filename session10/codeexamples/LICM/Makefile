build: 
	mkdir -p build;cd build; cmake ..;make; cd ..

run:
	clang -S -O1 -Xclang -disable-llvm-passes -emit-llvm ../test/licm.c -o ../test/licm.ll
	opt -passes=mem2reg -S ../test/licm.ll -o ../test/licm_mem2reg.ll
	opt -load-pass-plugin ./build/src/LICMPass.so -passes=licm-invariant -S ../test/licm_mem2reg.ll -o ../test/licm.ll.output 
	opt -passes=dot-cfg -cfg-dot-filename-prefix=licm ../test/licm.ll
	dot -Tpng licm.main.dot -o ../test/licm_before_hoisting.png
	opt -passes=dot-cfg -cfg-dot-filename-prefix=licm ../test/licm.ll.output
	dot -Tpng licm.main.dot -o ../test/licm_after_hoisting.png

clean:
	rm -f ../test/licm*.o
	rm -f ../test/licm*.output
	rm -rf build
	rm -f ../test/licm*.ll
	rm -f ../test/licm*.png
	rm -f *.dot

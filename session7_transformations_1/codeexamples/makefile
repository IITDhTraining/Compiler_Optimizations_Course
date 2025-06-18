#builds the pass plugin from scratch.
build: 
	cd pass-plugin; mkdir -p build;cd build; cmake .. -DCMAKE_CXX_FLAGS="-DEARLY_LINKING";make; cd ../..

#produces an IR file containing IR after transformation. -S option with opt for human readable form.
debug: clean
	cd pass-plugin; mkdir -p build;cd build; cmake ..;make; cd ../..
	clang -S -emit-llvm ./test/binaryop.c -o binaryop_before.ll
	opt -load-pass-plugin ./pass-plugin/build/src/mypass.so -passes='mypass' binaryop_before.ll -o binaryop_after.ll -S
	
#links the pass plugin and runs the pass on a test file
run:
	clang -fpass-plugin=./pass-plugin/build/src/mypass.so ./test/binaryop.c -o binaryop_transformed.out 
	./binaryop_transformed.out 500

#removes the plugin.  
clean:
	rm -rf ./pass-plugin/build *.out, *.ll

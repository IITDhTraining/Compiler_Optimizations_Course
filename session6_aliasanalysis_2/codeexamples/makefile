TESTCASE=test/aa1#change this to use your test program
TESTFLAG=-DALIAS_TEST#change this to -DALIAS_TEST or -DMODREF_TEST1 or -DMODREF_TEST2 to see other use cases.

#build your pass to test either ALIAS_TEST or MODREF_TEST1 or MODREF_TEST2
testbuild: 
	cd aa; mkdir -p build;cd build; cmake -DCMAKE_CXX_FLAGS=$(TESTFLAG) ..;make; cd ../..

runaa:$(TESTCASE).c
	clang -cc1 -disable-O0-optnone $(TESTFLAG) $(TESTCASE).c -emit-llvm -O0
	opt -load-pass-plugin=./aa/build/aa.so -passes="myaapass" -disable-output $(TESTCASE).ll

clean:
	rm -rf $(TESTCASE).ll 
	rm -rf ./aa/build 
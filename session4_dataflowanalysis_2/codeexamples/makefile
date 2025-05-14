TESTCASE=test/example4

reachingdefs: $(TESTCASE).c ./reachingdefs/reachingdefs.cpp
	clang -cc1 -disable-O0-optnone $< -emit-llvm  -O0
	opt -load-pass-plugin=./reachingdefs/build/reachingdefs.so -passes="my-module-pass" -disable-output  $(TESTCASE).ll

liveness: $(TESTCASE).c  ./liveness/liveness.cpp
	clang -cc1 -disable-O0-optnone $< -emit-llvm  -O0
	opt -load-pass-plugin=./liveness/build/liveness.so -passes="my-module-pass" -disable-output  $(TESTCASE).ll

clean:
	rm -f $(TESTCASE).ll 
	rm -f ./reachingdefs/build/reachingdefs.so ./liveness/build/liveness.so


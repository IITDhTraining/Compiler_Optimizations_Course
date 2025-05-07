TESTCASE=test/example2
cfg: $(TESTCASE).c
	clang -Xclang -emit-llvm -fsyntax-only $< 
	opt -passes=dot-cfg -cfg-dot-filename-prefix=$(TESTCASE) $(TESTCASE).ll
	dot -Tpng $(TESTCASE).main.dot -o $(TESTCASE).png

cfgwithphi: $(TESTCASE).c
	clang -Xclang -emit-llvm -fsyntax-only $< -O1 
	opt -passes=dot-cfg -cfg-dot-filename-prefix=$(TESTCASE)_withphi $(TESTCASE).ll
	dot -Tpng $(TESTCASE)_withphi.main.dot -o $(TESTCASE)_withphi.png

dominators: $(TESTCASE).c
	clang -O0 -emit-llvm -c $< -o $(TESTCASE).bc 
	opt -load-pass-plugin=./fnmodpass/build/MyPass.so -passes="my-module-pass" -disable-output  $(TESTCASE).bc

domfrontier: $(TESTCASE).c
	clang -O0 -emit-llvm -c $< -o $(TESTCASE).bc 
	opt -load-pass-plugin=./fnmodpass/build/MyPass.so -passes="my-module-pass" -disable-output  $(TESTCASE).bc

domtree: $(TESTCASE).c
	#clang -Xclang -emit-llvm -fsyntax-only $< -O0  
	clang -cc1 -disable-O0-optnone $< -emit-llvm  -O0
	opt -passes=dot-dom $(TESTCASE).ll
	dot -Tpng dom.main.dot -o $(TESTCASE)_dom.png

clean:
	rm -f $(TESTCASE).ll $(TESTCASE).test.dot $(TESTCASE).main.dot
	rm -f $(TESTCASE)_withphi.ll $(TESTCASE)_withphi.test.dot $(TESTCASE)_withphi.main.dot
	rm -f dom.test.dot dom.main.dot

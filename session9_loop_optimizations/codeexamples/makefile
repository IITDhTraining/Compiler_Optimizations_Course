#simplifies induction variable (eliminates)
indvarsimplify: invarsimplify.c
	clang -emit-llvm -S -Xclang -disable-O0-optnone $< -o invarsimplify.ll
	opt -passes=mem2reg -S invarsimplify.ll -o invarsimplify_promoted.ll
	opt -passes=indvars -S invarsimplify_promoted.ll -o invarsimplify.output
	
#  
clean:
	rm -rf *.ll *.output

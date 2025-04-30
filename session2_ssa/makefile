#this produces phi.ll, which you can inspect to see thephi nodes. 
#try -O0 optimization and see how the IR with -O1 is an improvement over that produced using -O0
phi: phi.c
	clang -cc1 $< -emit-llvm -O1

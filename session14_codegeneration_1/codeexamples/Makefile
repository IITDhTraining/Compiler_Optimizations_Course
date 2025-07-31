CC=clang
source=test.c #testlegalize.c

#build DAG from LLVM IR before first round of optimization
test: ${source}
#	clang -target i386-pc-linux-gnu -O0 -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	clang -O0 -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
	llc -debug-only=isel $@.ll 2> iseldump.txt
	llc -view-dag-combine1-dags $@.ll
	mv /tmp/dag*.dot $@.dot
	dot -Tpng $@.dot -o $@.png 

#optimize DAG before legalization of types
optimize1: test
	llc -view-legalize-dags $<.ll
	mv /tmp/dag*.dot $@.dot
	dot -Tpng $@.dot -o $@.png 

#legalize type and ops before second round of optimization
legalizeops: test optimize1
	llc -view-dag-combine2-dags $<.ll
	mv /tmp/dag*.dot $@.dot
	dot -Tpng $@.dot -o $@.png 

#perform second round of optimization before target machine instruction selection 
optimize2: test optimize1 legalizeops
	llc -view-isel-dags $<.ll
	mv /tmp/dag*.dot $@.dot
	dot -Tpng $@.dot -o $@.png

#select target machine instructions and create DAG
select: test optimize1 legalizeops optimize2
	llc -view-sched-dags $<.ll
	mv /tmp/dag*.dot $@.dot
	dot -Tpng $@.dot -o $@.png

legalizetype: legalizetype.ll
	llc -debug-only=isel-dump legalizetype.ll 2> iseldump.txt
	
clean:
	rm -f test.ll *.png *.dot *.s test iseldump.txt
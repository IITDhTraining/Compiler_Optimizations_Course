CC=clang
source=test.c

#get LLVM IR from source
test: ${source}
	clang -O0 -emit-llvm -S -Xclang -disable-O0-optnone $< -o $@.ll
#	clang -O3 -emit-llvm -S $< -o $@.ll

#get generic Machine IR (MIR) from LLVM IR.
gMIR: test
	llc -global-isel -stop-after=irtranslator -o - $<.ll > $<.gmir
#	llc -global-isel -march=bpf -stop-after=irtranslator -simplify-mir bpftest.ll > bpftest.gmir

#get generic MIR after the legalization operation
legalizer: test
	llc -O0 -global-isel -stop-after=legalizer -o - $<.ll > $<.legalizer

#get generic MIR after doing select reg bank. Note the constrains on the virtual registers compared to test.gmir obtained earlier.
selectregbank: test
#	llc -O0 -global-isel -stop-after=regbankselect -print-after-all $<.ll
	llc -O0 -global-isel -stop-after=regbankselect -o - $<.ll > $<.selectregbank

#Get instructions after instruction selection. Note that there will be no generic opcodes, virtual registers in test.isel 
isel: test
	llc -O0 -global-isel -stop-after=instruction-select -o - $<.ll > $<.isel

clean:
	rm -f test.ll test.s test.gmir test.isel test.legalizer test.selectregbank


#exercise: try the -print-after-all option the way shown above. What do you observe?
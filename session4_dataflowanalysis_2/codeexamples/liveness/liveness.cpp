#include<map>
#include "llvm/ADT/SetVector.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Module pass that loops over functions and reuses FAM
struct MyModulePass : PassInfoMixin<MyModulePass> {
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
        auto &FAMProxy = MAM.getResult<FunctionAnalysisManagerModuleProxy>(M);
        FunctionAnalysisManager &FAM = FAMProxy.getManager();

        errs() << "Module: " << M.getName() << "\n";

        for (Function &F : M) {
            if (F.isDeclaration())
                continue;

            errs() << "  [ModulePass] Function: " << F.getName() << "\n";
	    analyze(F);
            
            /*for (BasicBlock &BB : F) {
            	for (Instruction &I : BB) {
                            errs()<<I.getName()<<" instruction in BB "<<BB.getName()<<"\n";
		}
            }*/

        }

        return PreservedAnalyses::all();
    }

    void analyze(Function& F){
	    std::map<const BasicBlock*, SetVector<const Value*>> GEN, KILL; //use and def
	    std::map<const BasicBlock*, SetVector<const Value*>> IN, OUT;
	    for(BasicBlock& BB: F){
	    	SetVector<const Value*> tmpGEN, tmpKILL;
		for(Instruction& I:BB){
			for(const Use& operand: I.operands()){
				const Value* v=operand.get();
				if(isa<Instruction>(v) || isa<Argument>(v)){
					if(!tmpKILL.contains(v))
						tmpGEN.insert(v);
				}
			}
			tmpKILL.insert(&I);
		}
		GEN[&BB]=tmpGEN;
		KILL[&BB]=tmpKILL;
	    }
	    //worklist: comput IN, OUT for each BB
	    bool notConverged;
	    do{
		    notConverged=false;
		    for (BasicBlock &BB : F) {
			SetVector<const Value*> tmpIN, tmpOUT;

			// OUT[BB] = union of IN[succ] for all successors
			for (BasicBlock *succ : successors(&BB)) {
			    tmpOUT.set_union(IN[succ]);
			}

			// IN[BB] = GEN[BB] union (OUT[BB] - KILL[BB])
			tmpIN = GEN[&BB];
			for (auto &def : tmpOUT) {
			  if (KILL[&BB].contains(def))
			    tmpIN.insert(def);
			}

			if (IN[&BB] != tmpIN || OUT[&BB] != tmpOUT) {
			  IN[&BB] = tmpIN;
			  OUT[&BB] = tmpOUT;
			  notConverged = true;
			}
		}

	    }while(notConverged);

	    //print
	    for (auto &BB : F) {
		errs() << "Block " << BB.getName() << ":\n";
		errs() << "Live IN: ";
		for (auto *def : IN[&BB]) {
			errs() << def->getName()<<"  ";
		}
		errs() << "\n";

		errs() << "Live OUT: ";
		for (auto *def : OUT[&BB]) {
			errs() << def->getName()<<"  ";
		}
		errs() << "\n";
	    }
    } 
};

// Plugin registration
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "MyPassPlugin",
        LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "my-module-pass") {
                        MPM.addPass(MyModulePass());
                        return true;
                    }
                    return false;
                });
        }
    };
}

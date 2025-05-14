#include<map>
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
	    std::map<const BasicBlock*, std::set<const Instruction*>> GEN, KILL;
	    std::map<const Instruction*, std::set<const Instruction*>> IN, OUT;
	    for(BasicBlock& BB: F){
	    	std::set<const Instruction*> tmpGEN, tmpKILL;
		for(Instruction& I:BB){
			if(I.getType()->isVoidTy()) continue;
			//otherwise insert into gen set
			tmpGEN.insert(&I);
			//nothing for tmpKILL: why?
		}
		GEN[&BB]=tmpGEN;
		KILL[&BB]=tmpKILL;
	    }
	    //worklist: comput IN, OUT for each BB
	    bool notConverged;
	    do{
		    notConverged=false;
		    for (BasicBlock &BB : F) {
			std::set<const Instruction*> tmpIN, tmpOUT;

			// IN[BB] = union of OUT[pred] for all predecessors
			for (BasicBlock *Pred : predecessors(&BB)) {
			  auto it = OUT.find(Pred->getTerminator());
			  if (it != OUT.end())
			    tmpIN.insert(it->second.begin(), it->second.end());
			}

			// OUT[BB] = GEN[BB] union (IN[BB] - KILL[BB])
			tmpOUT = GEN[&BB];
			for (auto &def : tmpIN) {
			  if (KILL[&BB].find(def) == KILL[&BB].end())
			    tmpOUT.insert(def);
			}

			Instruction *lastInst = BB.getTerminator();
			if (IN[lastInst] != tmpIN || OUT[lastInst] != tmpOUT) {
			  IN[lastInst] = tmpIN;
			  OUT[lastInst] = tmpOUT;
			  notConverged = true;
			}
		}

	    }while(notConverged);

	    //print
	    for (auto &BB : F) {
		Instruction *term = BB.getTerminator();
		errs() << "Reaching defs(before): Block " << BB.getName() << ":\n";
		for (auto *def : IN[term]) {
			errs() << "  ";
			def->print(errs());
			errs() << "\n";
		}
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

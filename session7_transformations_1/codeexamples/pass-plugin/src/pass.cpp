#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include<vector>

using namespace llvm;

namespace {
//this pass replaces all occurrences of any binary operator with multiplication operator
struct TransformationPass : public PassInfoMixin<TransformationPass> {
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
	for(auto&F : M){
		std::vector<BinaryOperator*> binaryOps;
		for (auto& B : F) {
			for (auto& I : B) {
				//An instruction is also a value in LLVM. Check if the type of the value is BinaryOperator.
				if (auto* op = dyn_cast<BinaryOperator>(&I)) {
					//create a builder 
					IRBuilder<> builder(op);
					errs()<<"replacing with mul operator in Instruction: "<<*op<<"\n";
					//get two arguments to the binary operator.
					Value* arg0= op->getOperand(0);
					Value* arg1= op->getOperand(1);
					//create a new instruction (using builder) that multiplies the two arguments.
					Value* mul=builder.CreateMul(arg0, arg1);

					//check for all uses of the Value i.e. instruction with the binary op.
					//replace the use with new Value i.e. new instruction's result.
					for(auto& uses: op->uses()) {
						User* user=uses.getUser();
						user->setOperand(uses.getOperandNo(), mul);
					} 
					/*Alternatively, you can also use the following to replace the uses of old instruction.
					op->replaceAllUsesWith(mul);*/
					
					//add the old instruction to the list of binary ops to be removed.
					binaryOps.push_back(op);
				}
			}
	  	}
		//remove the old instruction as it is not needed anymore.
		for(auto & op : binaryOps) {
			op->eraseFromParent();
		}
	}

	

    return PreservedAnalyses::none();
    };
};

}

/* Implement the llvmGetPassPluginInfo method to register the pass. For this, need to 
 * return a struct of type: 
	struct PassPluginLibraryInfo {
	uint32_t APIVersion;
	const char *PluginName;
	const char *PluginVersion;
	void (*RegisterPassBuilderCallbacks)(PassBuilder &);
	};
	
	* APIVersion needs to be set to LLVM_PLUGIN_API_VERSION to ensure compatibility between different
	* llvm builds and the plugin. Always use the macro.
	* PluginName needs to be set as per chosen descriptive plugin name.
	* PluginVersion is user_defined value. Recommended to use LLVM_VERSION_STRING macro.
	* RegisterPassBuilderCallbacks is a function pointer to a function that returns void and accepts PassBuilder reference as an argument. 
	* Using the PassBuilder argument passed, you can register your pass with the pass manager.
	* The registerPipelineStartEPCallback lets you have your pass run early in the pipeline automatically before other LLVM default passes are added.
	* However, the registerPipelineStartEPCallback cannot be used to have early pass insertion in case of link-time pipelines.
	* E.g. with opt -load-pass-plugin=mypass.so -passes='mypass', your pass will not be recognized.
	* There is a registerPipelineParsingCallback that you can use to manually insert a pass into the pipeline (can be used with link-time pipelines).
	*/

#if EARLY_LINKING
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
	return {
        .APIVersion = LLVM_PLUGIN_API_VERSION,
        .PluginName = "mypass",
        .PluginVersion = LLVM_VERSION_STRING,
        .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
            PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel Level) {
                    MPM.addPass(TransformationPass());
                });
        }
    };
}

#else
extern "C" ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "mypass", LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "mypass") {
                        MPM.addPass(TransformationPass());
                        return true;
                    }
                    return false;
                });
        }};
}
#endif

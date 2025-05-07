#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/DominanceFrontier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Simple function pass that prints dominator info
struct MyFunctionPass : PassInfoMixin<MyFunctionPass> {
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
        DominatorTree &DT = FAM.getResult<DominatorTreeAnalysis>(F);

        DominanceFrontier &DF = FAM.getResult<DominanceFrontierAnalysis>(F);
        DF.analyze(DT);

        errs() << "Function: " << F.getName() << "\n";
        for (auto &BB : F) {
            const auto frontier = DF.find(&BB)->second;
            errs()<<"Dominance frontier of Block"<<BB.getName()<<":\n";
            if(frontier.empty())
                errs()<<" empty \n";
            else {
                for(auto &f: frontier){
                    errs()<<"\t"<<f->getName()<<"\n";
                }
            }
        }

        return PreservedAnalyses::all();
    }
};

// Module pass that loops over functions and reuses FAM
struct MyModulePass : PassInfoMixin<MyModulePass> {
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
        auto &FAMProxy = MAM.getResult<FunctionAnalysisManagerModuleProxy>(M);
        FunctionAnalysisManager &FAM = FAMProxy.getManager();

        errs() << "Module: " << M.getName() << "\n";

        for (Function &F : M) {
            if (F.isDeclaration())
                continue;

            DominatorTree &DT = FAM.getResult<DominatorTreeAnalysis>(F);
            errs() << "  [ModulePass] Function: " << F.getName() << "\n";
            
            /*for (BasicBlock &BB1 : F) {
                for(BasicBlock &BB2: F) {
                        if(DT.dominates(&BB1, &BB2)){
                            errs()<<BB1.getName()<<" dominates "<<BB2.getName()<<"\n";
                        }
                }
            }*/

            DominanceFrontier &DF = FAM.getResult<DominanceFrontierAnalysis>(F);
            DF.analyze(DT);
            errs() << "Function: " << F.getName() << "\n";
            for (auto &BB : F) {
                const auto frontier = DF.find(&BB)->second;
                errs()<<"Dominance frontier of Block "<<BB.getName()<<":\n";
                if(frontier.empty())
                    errs()<<" empty \n";
                else {
                    for(auto &f: frontier){
                        errs()<<"\t"<<f->getName()<<"\n";
                    }
                }
            }

            /*for (BasicBlock &BB : F) {
                DomTreeNode *Node = DT.getNode(&BB);
                if (Node) {
                    errs() << "    Block " << BB.getName() << " immediate dominator: ";
                    if (DomTreeNode *IDom = Node->getIDom()) {
                        errs() << IDom->getBlock()->getName() << "\n";
                    } else {
                        errs() << "none (entry)\n";
                    }
                }
            }*/
        }

        return PreservedAnalyses::all();
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
                [](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "my-func-pass") {
                        FPM.addPass(MyFunctionPass());
                        return true;
                    }
                    return false;
                });

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

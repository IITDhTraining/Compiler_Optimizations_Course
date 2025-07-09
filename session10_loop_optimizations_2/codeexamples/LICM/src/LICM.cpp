//Code adapted from https://github.com/neel-patel-1/GettingStartedWithBril/tree/main/lesson8
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"           // For DominatorTree
#include "llvm/Transforms/Utils/LoopUtils.h" // For InsertPreheaderForLoop
#include "llvm/Analysis/ValueTracking.h"   // For isSafeToSpeculativelyExecute
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

struct LICMInvariantModulePass : public PassInfoMixin<LICMInvariantModulePass> {
  bool checkInvariant(Loop &L, Value &V) {
    if (auto I = dyn_cast<Instruction>(&V)) {
      return !L.contains(I);
    }
    return true;
  }

  // Recursively process a loop until convergence
  bool processLoop(Loop *L, DominatorTree &DT, LoopInfo &LI) {
    bool modified = false;

    for (Loop *SubLoop : L->getSubLoops())
      modified |= processLoop(SubLoop, DT, LI);

    BasicBlock *Preheader = L->getLoopPreheader();
    if (!Preheader) {
      Preheader = InsertPreheaderForLoop(L, &DT, &LI, nullptr, false);
      if (!Preheader) {
        errs() << "Warning: Failed to insert preheader for loop: " << *L << "\n";
      } else {
        errs() << "Inserted preheader: " << Preheader->getName() << " for loop: " << *L << "\n";
        modified = true;
      }
    }

hoist:
    for (BasicBlock *BB : L->getBlocks()) {
      for (auto It = BB->begin(), End = BB->end(); It != End; ) {
        Instruction *Inst = &*It++;
        if (isa<PHINode>(Inst) || Inst->isTerminator())
          continue;
        if (!isSafeToSpeculativelyExecute(Inst))
          continue;
      
          bool allInvariant = true;
          for (int i=0; i<Inst->getNumOperands(); ++i) {
            if (!checkInvariant(*L, *Inst->getOperand(i))) {
              allInvariant = false;
              break;
            }
          }
          if (!allInvariant)
            continue;

        Inst->moveBefore(Preheader->getTerminator());
        modified = true;
        errs() << "Hoisted instruction: " << *Inst << "\n";
        goto hoist;
      }
    }
    return modified;
  }

  // Process every function in the module.
  bool processFunction(Function &F, LoopInfo &LI, DominatorTree &DT) {
    bool modified = false;
    errs() << "Processing function: " << F.getName() << "\n";
    for (Loop *L : LI)
      modified |= processLoop(L, DT, LI);
    return modified;
  }

  // Main entry point for the module pass.
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
    bool Modified = false;
    // Obtain a FunctionAnalysisManager for functions in the module.
    auto &FAM = MAM.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager();

    errs() << "Processing module: " << M.getName() << "\n";

    for (Function &F : M) {
      if (F.isDeclaration())
        continue;
      // Retrieve analyses needed for function F.
      auto &LI = FAM.getResult<LoopAnalysis>(F);
      auto &DT = FAM.getResult<DominatorTreeAnalysis>(F);
      Modified |= processFunction(F, LI, DT);
    }
    return (Modified ? PreservedAnalyses::none() : PreservedAnalyses::all());
  }
};

} // end anonymous namespace

// Register the pass so it can be invoked via "-passes=licm-invariant".
extern "C" LLVM_ATTRIBUTE_WEAK llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "LICMInvariantModulePass", "v0.1",
    [](PassBuilder &PB) {
      PB.registerPipelineParsingCallback(
        [](StringRef Name, llvm::ModulePassManager &MPM,
           ArrayRef<PassBuilder::PipelineElement>) {
          if (Name == "licm-invariant") {
            MPM.addPass(LICMInvariantModulePass());
            return true;
          }
          return false;
        });
    }
  };
}

#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

struct AliasCheckPass : PassInfoMixin<AliasCheckPass> {
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
        auto &FAMProxy = MAM.getResult<FunctionAnalysisManagerModuleProxy>(M);
        FunctionAnalysisManager &FAM = FAMProxy.getManager();

        errs() << "Module: " << M.getName() << "\n";

        for (Function &F : M) {
            if (F.isDeclaration())
                continue;
            errs() << "Running alias analysis on function: " << F.getName() << "\n";

                  // Get AA results from the analysis manager
            AliasAnalysis &AA = FAM.getResult<AAManager>(F);
#if ALIAS_TEST
            errs()<<" Checking two pointers if they alias or not\n";
            // Example: Find two pointer values to check aliasing
            const Value *PtrA = nullptr, *PtrB = nullptr;

            for (const Instruction &I : instructions(F)) {
              if (const AllocaInst *AI = dyn_cast<AllocaInst>(&I)) {
                if (!PtrA)
                  PtrA = AI;
                else {
                  PtrB = AI;
                  break;
                }
              }
            }

            if (PtrA && PtrB) {
              AliasResult result = AA.alias(PtrA, LocationSize::precise(4), PtrB, LocationSize::precise(4));
              errs() << "Alias analysis result between two allocas: ";
              switch (result) {
                case AliasResult::Kind::NoAlias:     errs() << "NoAlias\n"; break;
                case AliasResult::Kind::MayAlias:    errs() << "MayAlias\n"; break;
                case AliasResult::Kind::MustAlias:   errs() << "MustAlias\n"; break;
                case AliasResult::Kind::PartialAlias:errs() << "PartialAlias\n"; break;
              }
            }

#endif

#if MODREF_TEST1
            errs()<<" MODREF_TEST1: checking if a function call modifies or reads a memory location\n";
            for (Instruction &I : instructions(F)) {
      if (auto *Call = dyn_cast<CallBase>(&I)) {
        errs() << "Analyzing call: " << *Call << "\n";

        for (Instruction &J : instructions(F)) {
          if (auto *Store = dyn_cast<StoreInst>(&J)) {
            MemoryLocation Loc = MemoryLocation::get(Store);

            ModRefInfo MRI = AA.getModRefInfo(Call, Loc);
            errs() << "  Against store: " << Store << " → ";

            switch (MRI) {
              case ModRefInfo::NoModRef:
                errs() << "NoModRef\n";
                break;
              case ModRefInfo::Mod:
                errs() << "Mod (writes only)\n";
                break;
              case ModRefInfo::Ref:
                errs() << "Ref (reads only)\n";
                break;
              case ModRefInfo::ModRef:
                errs() << "ModRef (reads & writes)\n";
                break;
              default:
                errs() << "Unknown\n";
                break;
            }
          }
        }
      }
    }
  #endif

  #if MODREF_TEST2
              errs()<<" MODREF_TEST2: checking if two function calls interfere with each other\n";
        SmallVector<CallBase*, 8> Calls;

          // Collect all function calls in the function
          for (Instruction &I : instructions(F)) {
            if (auto *CB = dyn_cast<CallBase>(&I)) {
              Calls.push_back(CB);
            }
          }

          // Compare each pair of calls
          for (size_t i = 0; i < Calls.size(); ++i) {
            for (size_t j = i + 1; j < Calls.size(); ++j) {
              CallBase *CallA = Calls[i];
              CallBase *CallB = Calls[j];

              ModRefInfo Info = AA.getModRefInfo(CallA, CallB);

              errs() << "Checking interference between:\n"
                    << "  Call A: " << *CallA << "\n"
                    << "  Call B: " << *CallB << "\n"
                    << "  ModRefInfo: ";

              switch (Info) {
                case ModRefInfo::NoModRef:   errs() << "NoModRef (safe)\n"; break;
                case ModRefInfo::Mod:        errs() << "Mod (A writes to B)\n"; break;
                case ModRefInfo::Ref:        errs() << "Ref (A reads from B)\n"; break;
                case ModRefInfo::ModRef:     errs() << "ModRef (A reads/writes to B)\n"; break;
                default:                     errs() << "Unknown\n"; break;
              }
            }
          } //endfor
  #endif
        } //endfor
        return PreservedAnalyses::all();
    }


};

// Plugin registration
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "myaapass",
        LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM, ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "myaapass") {
                        MPM.addPass(AliasCheckPass());
                        return true;
                    }
                    return false;
                });
        }
    };
  }
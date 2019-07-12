#ifndef LLVM_LIB_TARGET_NPEngine_NPEngineTARGETMACHINE_H
#define LLVM_LIB_TARGET_NPEngine_NPEngineTARGETMACHINE_H

#include "MCTargetDesc/NPEngineMCTargetDesc.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class NPEngineTargetMachine : public LLVMTargetMachine {
//std::unique_ptr<TargetLoweringObjectFile> TLOF;
  //NPEngineSubtarget Subtarget;

public:
  NPEngineTargetMachine(const Target &T,StringRef TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                     CodeGenOpt::Level OL);

//  const NPEngineSubtarget *getSubtargetImpl(const Function &) const override {
  //  return &Subtarget;
  //}

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

 // TargetLoweringObjectFile *getObjFileLowering() const override {
   // return TLOF.get();
  //}
};
}

#endif

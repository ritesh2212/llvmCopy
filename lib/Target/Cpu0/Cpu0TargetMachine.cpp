//===-- Cpu0TargetMachine.cpp - Define TargetMachine for Cpu0 -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Cpu0 target spec.
//
//===----------------------------------------------------------------------===//

 #include "Cpu0TargetMachine.h"
  #include "Cpu0FrameLowering.h"
 #include "Cpu0.h"
  #include "Cpu0TargetObjectFile.h"
 // #include "Cpu0TargetTransformInfo.h"
  #include "llvm/Analysis/TargetTransformInfo.h"
  #include "llvm/CodeGen/Passes.h"
  #include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
  #include "llvm/CodeGen/TargetPassConfig.h"
  #include "llvm/Support/FormattedStream.h"
  #include "llvm/Support/TargetRegistry.h"
  #include "llvm/Target/TargetOptions.h"
 #include <iostream>
using namespace llvm;

#define DEBUG_TYPE "cpu0"

Target llvm::TheCpu0Target;
extern "C" void LLVMInitializeCpu0Target() {
	errs()<<"Came here!!!!!!!!!!!!!!!!!!!!!!!!";
	RegisterTargetMachine<Cpu0TargetMachine> X(TheCpu0Target);	
//RegisterTargetMachine<Cpu0TargetMachine> registered_target(TheCpu0Target);//getTheCpu0Target());  
 }

static std::string computeDataLayout() {
  return "E"        // Big endian
           "-m:e"     // ELF name manging
           "-p:32:32" // 32-bit pointers, 32 bit aligned
           "-i64:64"  // 64 bit integers, 64 bit aligned
           "-a:0:32"  // 32 bit alignment of objects of aggregate type
           "-n32"     // 32 bit native integer width
           "-S64";    // 64 bit natural stack alignment

}

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::Static;
  return *RM;
}

Cpu0TargetMachine::Cpu0TargetMachine(const Target &T, const Triple &TT,
                                         StringRef Cpu, StringRef FeatureString,
                                         const TargetOptions &Options,
                                         Optional<Reloc::Model> RM,
                                         Optional<CodeModel::Model> CodeModel,
                                         CodeGenOpt::Level OptLevel, bool JIT)
      : LLVMTargetMachine(T, computeDataLayout(), TT, Cpu, FeatureString, Options,
                          getEffectiveRelocModel(RM),
                          getEffectiveCodeModel(CodeModel, CodeModel::Medium),
                          OptLevel),
	       Subtarget(TT, Cpu, FeatureString, *this, Options, getCodeModel(),
	      		 OptLevel),
       TLOF(make_unique<TargetLoweringObjectFileELF>()){
std::cout<<"sdfgrgregerregerergergege";
initAsmInfo();
}
Cpu0TargetMachine::~Cpu0TargetMachine() {} 




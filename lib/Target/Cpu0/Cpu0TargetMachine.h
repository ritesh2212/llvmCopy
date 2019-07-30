
//===-- Cpu0TargetMachine.h - Define TargetMachine for Cpu0 --- C++ ---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Cpu0 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//


#ifndef LLVM_LIB_TARGET_CPU0_CPU0TARGETMACHINE_H
#define LLVM_LIB_TARGET_CPU0_CPU0TARGETMACHINE_H

#include "Cpu0InstrInfo.h"
#include "Cpu0Subtarget.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
	class formatted_raw_ostream;
	
	class Cpu0TargetMachine : public LLVMTargetMachine {
	Cpu0Subtarget Subtarget;
	std::unique_ptr<TargetLoweringObjectFile> TLOF;
	public:
		Cpu0TargetMachine(const Target &TheTarget, const Triple &TargetTriple,
	                          StringRef Cpu, StringRef FeatureString,
 	                          const TargetOptions &Options,
 	                          Optional<Reloc::Model> RelocationModel,
 	                          Optional<CodeModel::Model> CodeModel,
 	                          CodeGenOpt::Level OptLevel, bool JIT);
 		~Cpu0TargetMachine() override;  // Taken from Hexagon codebase
		const Cpu0Subtarget *getSubtargetImpl(const llvm::Function & /*Fn*/) const override {
			
			return &Subtarget;
		}
  
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
	};
}// namespace llvm
#endif

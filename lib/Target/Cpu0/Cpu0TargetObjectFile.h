//===-- Cpu0TargetObjectFile.h -----------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0TARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_CPU0_CPU0TARGETOBJECTFILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/MC/MCSectionELF.h"

namespace llvm {

  class Cpu0TargetObjectFile : public TargetLoweringObjectFileELF {
    MCSection *SmallDataSection;
    MCSection *SmallBSSSection;
    //const Cpu0TargetMachine *TM;
  public:
    void Initialize(MCContext &Ctx, const TargetMachine &TM) override;

  };
} // end namespace llvm

#endif


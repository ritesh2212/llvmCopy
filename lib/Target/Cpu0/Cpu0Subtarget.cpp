
//===- Cpu0Subtarget.cpp - Lanai Subtarget Information -----------*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Cpu0 specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "Cpu0Subtarget.h"

#include "Cpu0.h"

#define DEBUG_TYPE "cpu0-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "Cpu0GenSubtargetInfo.inc"

using namespace llvm;


static cl::opt<bool> EnableOverflowOpt
                ("cpu0-enable-overflow", cl::Hidden, cl::init(false),
                 cl::desc("Use trigger overflow instructions add and sub \
                 instead of non-overflow instructions addu and subu"));





void Cpu0Subtarget::initSubtargetFeatures(StringRef CPU, StringRef FS) {
  std::string CPUName = CPU;
  if (CPUName.empty())
    CPUName = "generic";

  ParseSubtargetFeatures(CPUName, FS);
}

Cpu0Subtarget &Cpu0Subtarget::initializeSubtargetDependencies(StringRef CPU,
                                                                StringRef FS) {
  initSubtargetFeatures(CPU, FS);
  return *this;
}

Cpu0Subtarget::Cpu0Subtarget(const Triple &TargetTriple, StringRef Cpu,
                               StringRef FeatureString, const TargetMachine &TM,
                               const TargetOptions & /*Options*/,
                               CodeModel::Model /*CodeModel*/,
                               CodeGenOpt::Level /*OptLevel*/)
    : Cpu0GenSubtargetInfo(TargetTriple, Cpu, FeatureString),
     FrameLowering(initializeSubtargetDependencies(Cpu, FeatureString)),
     InstrInfo() 
{
    EnableOverflow = EnableOverflowOpt;


}

//===- TOYSubtarget.cpp - TOY Subtarget Information -----------*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the TOY specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "TOYSubtarget.h"
#include "llvm/Support/TargetRegistry.h"
#include "TOY.h"

#define DEBUG_TYPE "toy-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "TOYGenSubtargetInfo.inc"

using namespace llvm;

void TOYSubtarget::TOYSubtarget(const std::string &TT, const
std::string &CPU, const std::string &FS, TOYTargetMachine &TM):TOYGenSubtargetInfo(TT, CPU, FS), InstrInfo(), FrameLowering(*this),
      TLInfo(TM, *this) {}


//===-- Cpu0FrameLowering.cpp - Cpu0 Frame Information ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Cpu0 implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "Cpu0FrameLowering.h"

//#include "Cpu0AluCode.h"
#include "Cpu0InstrInfo.h"
#include "Cpu0Subtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/IR/Function.h"

using namespace llvm;

void Cpu0FrameLowering::determineFrameLayout(MachineFunction &MF) const {
}

void Cpu0FrameLowering::replaceAdjDynAllocPseudo(MachineFunction &MF) const{
}
void Cpu0FrameLowering::emitPrologue(MachineFunction &MF,
                                       MachineBasicBlock &MBB) const {
}

MachineBasicBlock::iterator Cpu0FrameLowering::eliminateCallFramePseudoInstr(MachineFunction & /*MF*/, MachineBasicBlock &MBB, MachineBasicBlock::iterator I) const {
}

void Cpu0FrameLowering::emitEpilogue(MachineFunction & /*MF*/,
                                       MachineBasicBlock &MBB) const {
}
void Cpu0FrameLowering::determineCalleeSaves(MachineFunction &MF,
                                               BitVector &SavedRegs,
                                               RegScavenger *RS) const {
}


//Cpu0FrameLowering::~Cpu0FrameLowering(){
//}

//Cpu0FrameLowering(Cpu0Subtarget &Subtarget)
//      : TargetFrameLowering(StackGrowsDown,
                            /*StackAlignment=*///8,
                            /*LocalAreaOffset=*///0),
  //      STI(Subtarget) {}


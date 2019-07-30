//===-- Cpu0FrameLowering.h - Define frame lowering for Lanai --*- C++-*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class implements Cpu0-specific bits of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0FRAMELOWERING_H
#define LLVM_LIB_TARGET_CPU0_CPU0FRAMELOWERING_H
#include "Cpu0.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class BitVector;
class Cpu0Subtarget;

class Cpu0FrameLowering : public TargetFrameLowering {
private:
  void determineFrameLayout(MachineFunction &MF) const;
  void replaceAdjDynAllocPseudo(MachineFunction &MF) const;

protected:
  const Cpu0Subtarget &STI;

public:
  explicit Cpu0FrameLowering(const Cpu0Subtarget &Subtarget)
      : TargetFrameLowering(StackGrowsDown,
                            /*StackAlignment=*/8,
                            /*LocalAreaOffset=*/0),
        STI(Subtarget) {}

  // emitProlog/emitEpilog - These methods insert prolog and epilog code into
  // the function.
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  MachineBasicBlock::iterator
  eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator I) const override;

  bool hasFP(const MachineFunction & /*MF*/) const override { return true; }

  void determineCalleeSaves(MachineFunction &MF, BitVector &SavedRegs,
                            RegScavenger *RS = nullptr) const override;
  //~Cpu0FrameLowering();
};

} // namespace llvm

#endif // LLVM_LIB_TARGET_CPU0_CPU0FRAMELOWERING_H

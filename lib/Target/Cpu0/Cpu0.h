//===-- Cpu0.h - Top-level interface for Cpu0 representation ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM Cpu0 back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CPU0_CPU0_H
#define LLVM_LIB_TARGET_CPU0_CPU0_H

#include "MCTargetDesc/Cpu0MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Pass.h"


namespace llvm {
	class Cpu0TargetMachine;
	class FunctionPass;
	class formatted_raw_ostream;
	// createCpu0ISelDag - This pass converts a legalized DAG into a
	// Cpu0-specific DAG, ready for instruction scheduling.0
	FunctionPass *createCpu0ISelDag(Cpu0TargetMachine &TM);
//	Target &getTheCpu0Target();
} // end namespace llvm;

#endif

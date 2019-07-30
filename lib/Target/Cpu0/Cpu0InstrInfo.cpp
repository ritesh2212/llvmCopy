//===-- Cpu0InstrInfo.cpp - Cpu0 Instruction Information ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Cpu0 implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "Cpu0.h"
#include "Cpu0InstrInfo.h"
//#include "Cpu0MachineFunctionInfo.h"
#include "Cpu0TargetMachine.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "Cpu0GenInstrInfo.inc"

Cpu0InstrInfo::Cpu0InstrInfo()
    : Cpu0GenInstrInfo(){}//Cpu0::ADJCALLSTACKDOWN, Cpu0::ADJCALLSTACKUP){}


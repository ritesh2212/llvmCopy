//===- Cpu0.td - Describe the Lanai Target Machine --------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Register File, Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//
include "Cpu0RegisterInfo.td"
include "Cpu0Schedule.td"
include "Cpu0InstrInfo.td"
//include "Cpu0RegisterInfoGPROutForOther.td"

def Cpu0InstrInfo : InstrInfo;

def : ProcessorModel<"generic", Cpu0SchedModel, []>;
def : ProcessorModel<"v11", Cpu0SchedModel, []>;

def Cpu0 : Target{
	let InstructionSet = Cpu0InstrInfo;
	}



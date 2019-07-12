//===- TOY.td - Describe the TOY Target Machine --------*- tablegen -*-===//
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

include "TOYRegisterInfo.td"
include "TOYCallingConv.td"
include "TOYInstrInfo.td"

def TOYInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// TOY processors supported.
//===----------------------------------------------------------------------===//

def TOYInstPrinter : AsmWriter {
  string AsmWriterClassName  = "InstPrinter";
  bit isMCAsmWriter = 1;
}

//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//

def TOY : Target {
  // Pull in Instruction Info:
  let InstructionSet = TOYInstrInfo;
  let AssemblyWriters = [TOYInstPrinter];
}

//===----------------------------------------------------------------------===//
// Implementing Subtarget ADD
//===----------------------------------------------------------------------===//

//def ADDrr : SubtargetFeature<"addrr","hasADDrr","true","Enable add rr for toy">;

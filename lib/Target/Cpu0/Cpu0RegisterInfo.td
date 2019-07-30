//===-- Cpu0RegisterInfo.td - Cpu0 Register defs ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// We have bank of 32 registers.
class Cpu0Reg<string n> : Register<n> {
  field bits<5> Num;
  let Namespace = "Cpu0";
}

// Cpu0 CPU Registers
class Cpu0GPRReg<bits<5> num, string n> : Cpu0Reg<n> {
  let Num = num;
}

//===----------------------------------------------------------------------===//
//  Registers
//===----------------------------------------------------------------------===//

let Namespace = "Cpu0" in {
  // General Purpose Registers
  def ZERO : Cpu0GPRReg<0, "zero">, DwarfRegNum<[ 0 ]>;
  def AT : Cpu0GPRReg<1, "at">, DwarfRegNum<[ 1 ]>;
  foreach RegNum = 2 - 23 in {
    def R #RegNum : Cpu0GPRReg<RegNum, "r" #RegNum>, DwarfRegNum<[ RegNum ]>;
  }
  def SW   : Cpu0GPRReg<15, "sw">,   DwarfRegNum<[15]>;
  def ET : Cpu0GPRReg<24, "et">, DwarfRegNum<[ 24 ]>;
  def BT : Cpu0GPRReg<25, "bt">, DwarfRegNum<[ 25 ]>;
  def GP : Cpu0GPRReg<26, "gp">, DwarfRegNum<[ 26 ]>;
  def SP : Cpu0GPRReg<27, "sp">, DwarfRegNum<[ 27 ]>;
  def FP : Cpu0GPRReg<28, "fp">, DwarfRegNum<[ 28 ]>;
  def EA : Cpu0GPRReg<29, "ea">, DwarfRegNum<[ 29 ]>;
  def BA : Cpu0GPRReg<30, "ba">, DwarfRegNum<[ 30 ]>;
  def RA : Cpu0GPRReg<31, "ra">, DwarfRegNum<[ 31 ]>;
 // def SR     : RegisterClass<"Cpu0", [i32], 32, (add SW)>;
  def PC : Cpu0Reg<"pc">, DwarfRegNum<[ 32 ]>;
}

//===----------------------------------------------------------------------===//
// Register Classes
//===----------------------------------------------------------------------===//

def CPURegs : RegisterClass<"Cpu0", [ i32 ], 32,
                            (add
                            // Reserved
                            ZERO,
                            AT,
                            // Return Values and Arguments
                            (sequence "R%u", 2, 7),
                            // Not preserved across procedure calls
                            // Caller saved
                            (sequence "R%u", 8, 15),
                            // Callee saved
                            (sequence "R%u", 16, 23),
                            // Reserved
                            ET, BT, GP, SP, FP, EA, BA, RA, PC)>;

def GPROut : RegisterClass<"Cpu0", [i32], 32, (add (sub CPURegs, SW))>;
def SR     : RegisterClass<"Cpu0", [i32], 32, (add SW)>;


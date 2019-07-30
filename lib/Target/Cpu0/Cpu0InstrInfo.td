//===- Cpu0InstrInfo.td - Target Description for Nios2 ------*- tablegen -*-=//
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

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

include "Cpu0InstrFormats.td"

//===----------------------------------------------------------------------===//
// Cpu0 Operand, Complex Patterns and Transformations Definitions.
//===----------------------------------------------------------------------===//


def SDT_Cpu0Ret          : SDTypeProfile<0, 1, [SDTCisInt<0>]>;
def SDT_Cpu0JmpLink      : SDTypeProfile<0, 1, [SDTCisVT<0, iPTR>]>;
def SDT_Cpu0CallSeqStart : SDCallSeqStart<[SDTCisVT<0, i32>]>;
def SDT_Cpu0CallSeqEnd   : SDCallSeqEnd<[SDTCisVT<0, i32>, SDTCisVT<1, i32>]>;

//def SDT_Cpu0JmpLink      : SDTypeProfile<0, 1, [SDTCisVT<0, iPTR>]>;
def SDT_Cpu0DivRem       : SDTypeProfile<0, 2,
                                         [SDTCisInt<0>,
                                          SDTCisSameAs<0, 1>]>;



// Call
def Cpu0JmpLink : SDNode<"Cpu0ISD::JmpLink",SDT_Cpu0JmpLink,
                         [SDNPHasChain, SDNPOutGlue, SDNPOptInGlue,
                          SDNPVariadic]>;


def Cpu0TailCall : SDNode<"Cpu0ISD::TailCall", SDT_Cpu0JmpLink,
                          [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;





// Signed Operand
def simm16      : Operand<i32> {
  let DecoderMethod= "DecodeSimm16";
}

def shamt       : Operand<i32>;

def uimm16      : Operand<i32> {
  let PrintMethod = "printUnsignedImm";
}

def LO16 : SDNodeXForm<imm, [{
  return getImm(N, N->getZExtValue() & 0xffff);
}]>;

// Node immediate fits as 16-bit zero extended on target immediate.
// The LO16 param means that only the lower 16 bits of the node
// immediate are caught.
// e.g. addiu, sltiu
def immZExt16  : PatLeaf<(imm), [{
  if (N->getValueType(0) == MVT::i32)
    return (uint32_t)N->getZExtValue() == (unsigned short)N->getZExtValue();
  else
    return (uint64_t)N->getZExtValue() == (unsigned short)N->getZExtValue();
}], LO16>;

// Immediate can be loaded with LUi (32-bit int with lower 16-bit cleared).
def immLow16Zero : PatLeaf<(imm), [{
  int64_t Val = N->getSExtValue();
  return isInt<32>(Val) && !(Val & 0xffff);
}]>;

// shamt field must fit in 5 bits.
def immZExt5 : ImmLeaf<i32, [{return Imm == (Imm & 0x1f);}]>;






def mem : Operand<iPTR> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops CPURegs, simm16);
  let EncoderMethod = "getMemEncoding";
  //let ParserMatchClass = Cpu0MemAsmOperand;
}




// Node immediate fits as 16-bit sign extended on target immediate.
// e.g. addi, andi
def immSExt16  : PatLeaf<(imm), [{ return isInt<16>(N->getSExtValue()); }]>;
// Cpu0 Address Mode! SDNode frameindex could possibily be a match
// since load and store instructions from stack used it.
def addr : 
  ComplexPattern<iPTR, 2, "SelectAddr", [frameindex], [SDNPWantParent]>;

class AlignedLoad<PatFrag Node> :
  PatFrag<(ops node:$ptr), (Node node:$ptr), [{
  LoadSDNode *LD = cast<LoadSDNode>(N);
  return LD->getMemoryVT().getSizeInBits()/8 <= LD->getAlignment();
}]>;

class AlignedStore<PatFrag Node> :
  PatFrag<(ops node:$val, node:$ptr), (Node node:$val, node:$ptr), [{
  StoreSDNode *SD = cast<StoreSDNode>(N);
  return SD->getMemoryVT().getSizeInBits()/8 <= SD->getAlignment();
}]>;

def load_a          : AlignedLoad<load>;

def store_a         : AlignedStore<store>;

//===----------------------------------------------------------------------===//
// Instructions specific format
//===----------------------------------------------------------------------===//

class ArithLogicR<bits<8> op, string instr_asm, SDNode OpNode,
                  InstrItinClass itin, RegisterClass RC, bit isComm = 0>:
  FA<op, (outs GPROut:$ra), (ins RC:$rb, RC:$rc),
     !strconcat(instr_asm, "\t$ra, $rb, $rc"),
     [(set GPROut:$ra, (OpNode RC:$rb, RC:$rc))], itin> {
  let shamt = 0;
  let isCommutable = isComm;	// e.g. add rb rc =  add rc rb
  let isReMaterializable = 1;
}

class CmpInstr<bits<8> op, string instr_asm, 
               InstrItinClass itin, RegisterClass RC, RegisterClass RD, 
               bit isComm = 0>:
  FA<op, (outs RD:$ra), (ins RC:$rb, RC:$rc),
     !strconcat(instr_asm, "\t$ra, $rb, $rc"), [], itin> {
  let shamt = 0;
  let isCommutable = isComm;
  //let Predicates = [HasCmp];
}

class Cpu0InstAlias<string Asm, dag Result, bit Emit = 0b1> :
  InstAlias<Asm, Result, Emit>;


// Arithmetic and logical instructions with 2 register operands.
class ArithLogicI<bits<8> op, string instr_asm, SDNode OpNode,
                  Operand Od, PatLeaf imm_type, RegisterClass RC> :
  FL<op, (outs GPROut:$ra), (ins RC:$rb, Od:$imm16),
     !strconcat(instr_asm, "\t$ra, $rb, $imm16"),
     [(set GPROut:$ra, (OpNode RC:$rb, imm_type:$imm16))], IIAlu> {
  let isReMaterializable = 1;
}


//Shifts

class shift_rotate_imm<bits<8> op, bits<4> isRotate, string instr_asm,
                       SDNode OpNode, PatFrag PF, Operand ImmOpnd,
                       RegisterClass RC>:
  FA<op, (outs GPROut:$ra), (ins RC:$rb, ImmOpnd:$shamt),
     !strconcat(instr_asm, "\t$ra, $rb, $shamt"),
     [(set GPROut:$ra, (OpNode RC:$rb, PF:$shamt))], IIAlu> {
  let rc = 0;
}

// 32-bit shift instructions.
class shift_rotate_imm32<bits<8> op, bits<4> isRotate, string instr_asm,
                         SDNode OpNode>:
  shift_rotate_imm<op, isRotate, instr_asm, OpNode, immZExt5, shamt, CPURegs>;




class shift_rotate_reg<bits<8> op, bits<4> isRotate, string instr_asm,
                       SDNode OpNode, RegisterClass RC>:
  FA<op, (outs GPROut:$ra), (ins RC:$rb, RC:$rc),
     !strconcat(instr_asm, "\t$ra, $rb, $rc"),
     [(set GPROut:$ra, (OpNode RC:$rb, RC:$rc))], IIAlu> {
  let shamt = 0;
}

class LoadUpper<bits<8> op, string instr_asm, RegisterClass RC, Operand Imm>:
  FL<op, (outs RC:$ra), (ins Imm:$imm16),
     !strconcat(instr_asm, "\t$ra, $imm16"), [], IIAlu> {
  let rb = 0;
  let isReMaterializable = 1;
}


class FMem<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern,
          InstrItinClass itin>: FL<op, outs, ins, asmstr, pattern, itin> {
  bits<20> addr;
  let Inst{19-16} = addr{19-16};
  let Inst{15-0}  = addr{15-0};
  let DecoderMethod = "DecodeMem";
}

let canFoldAsLoad = 1 in
class LoadM<bits<8> op, string instr_asm, PatFrag OpNode, RegisterClass RC,
            Operand MemOpnd, bit Pseudo>:
  FMem<op, (outs RC:$ra), (ins MemOpnd:$addr),
     !strconcat(instr_asm, "\t$ra, $addr"),
     [(set RC:$ra, (OpNode addr:$addr))], IILoad> {
  let isPseudo = Pseudo;
}

class StoreM<bits<8> op, string instr_asm, PatFrag OpNode, RegisterClass RC,
             Operand MemOpnd, bit Pseudo>:
  FMem<op, (outs), (ins RC:$ra, MemOpnd:$addr),
     !strconcat(instr_asm, "\t$ra, $addr"),
     [(OpNode RC:$ra, addr:$addr)], IIStore> {
  let isPseudo = Pseudo;
}

//@ 32-bit load
  class LoadM32<bits<8> op, string instr_asm, PatFrag OpNode,
              bit Pseudo=0>:
   FMem<op, (outs GPROut:$dst), (ins mem:$addr),
      !strconcat(instr_asm, "\t$dst, $addr"),
      [(set GPROut:$dst, (OpNode addr:$addr))], IILoad> {
   let isPseudo = Pseudo;
 }



// 32-bit store.
class StoreM32<bits<8> op, string instr_asm, PatFrag OpNode,
                    bit Pseudo = 0>:
  FMem<op, (outs), (ins GPROut:$src, mem:$addr),
      !strconcat(instr_asm, "\t$src, $addr"),
      [(OpNode GPROut:$src, addr:$addr)], IIStore> {
   let isPseudo = Pseudo;
 }



//@JumpFR {
let isBranch=1, isTerminator=1, isBarrier=1, imm16=0, hasDelaySlot = 1,
    isIndirectBranch = 1 in
class JumpFR<bits<8> op, string instr_asm, RegisterClass RC>:
  FL<op, (outs), (ins RC:$ra),
     !strconcat(instr_asm, "\t$ra"), [(brind RC:$ra)], IIBranch> {
  let rb = 0;
  let imm16 = 0;
}
//@JumpFR }

//Return instruction

class RetBase<RegisterClass RC>: JumpFR<0x3c, "ret", RC> {
  let isReturn = 1;
  let isCodeGenOnly = 1;
  let hasCtrlDep = 1;
  let hasExtraSrcRegAllocReq = 1;
}


/// Load and Store Instructions
///  aligned
def LD     : LoadM32<0x01,  "ld",  load_a>;
def ST     : StoreM32<0x02, "st",  store_a>;

def ADDiu   : ArithLogicI<0x09, "addiu", add, simm16, immSExt16, CPURegs>;
def ANDi    : ArithLogicI<0x0c, "andi", and, uimm16, immZExt16, CPURegs>;
def ORi     : ArithLogicI<0x0d, "ori", or, uimm16, immZExt16, CPURegs>;
def XORi    : ArithLogicI<0x0e, "xori", xor, uimm16, immZExt16, CPURegs>;
def LUi     : LoadUpper<0x0f, "lui", GPROut, uimm16>;
def CMP     : CmpInstr<0x10, "cmp", IIAlu, CPURegs, SR, 0>;
def ADDu    : ArithLogicR<0x11, "addu", add, IIAlu, CPURegs, 1>;
def SUBu    : ArithLogicR<0x12, "subu", sub, IIAlu, CPURegs>;
def ADD     : ArithLogicR<0x13, "add", add, IIAlu, CPURegs, 1>;
def SUB     : ArithLogicR<0x14, "sub", sub, IIAlu, CPURegs>;
def AND     : ArithLogicR<0x18, "and", and, IIAlu, CPURegs, 1>;
def OR      : ArithLogicR<0x19, "or", or, IIAlu, CPURegs, 1>;
def XOR     : ArithLogicR<0x1a, "xor", xor, IIAlu, CPURegs, 1>;
def SHL     : shift_rotate_imm32<0x1e, 0x00, "shl", shl>;
// srl is IR node for lshr llvm IR instruction of .bc
def SHR     : shift_rotate_imm32<0x1f, 0x00, "shr", srl>;
def SRAV    : shift_rotate_reg<0x20, 0x00, "srav", sra, CPURegs>;
def SHLV    : shift_rotate_reg<0x21, 0x00, "shlv", shl, CPURegs>;
def SHRV    : shift_rotate_reg<0x22, 0x00, "shrv", srl, CPURegs>;
def ROLV    : shift_rotate_reg<0x23, 0x01, "rolv", rotl, CPURegs>;
def RORV    : shift_rotate_reg<0x24, 0x01, "rorv", rotr, CPURegs>;

def : Cpu0InstAlias<"move $dst, $src",
                    (ADDu GPROut:$dst, GPROut:$src,ZERO), 1>;

def : Pat<(not CPURegs:$in),
// 1: in == 0; 0: in != 0
          (XORi CPURegs:$in, 1)>;






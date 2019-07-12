  //===- TOYInstrFormats.td - TOY Instruction Formats ----*- tablegen -*-===//
  //
  //                     The LLVM Compiler Infrastructure
  //
  // This file is distributed under the University of Illinois Open Source
  // License. See LICENSE.TXT for details.
  //
  //===----------------------------------------------------------------------===//
  
 class InstTOY<dag outs, dag ins, string asmstr, list<dag> pattern>
     : Instruction {
   field bits<32> Inst;
   field bits<32> SoftFail = 0;
   let Size = 4;
 
   let Namespace = "TOY";
   let DecoderNamespace = "TOY";
 
   bits<4> Opcode;
   let Inst{31 - 28} = Opcode;
  
   dag OutOperandList = outs;
   dag InOperandList = ins;
   let AsmString = asmstr;
   let Pattern = pattern;
 }














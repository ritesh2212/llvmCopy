class InstTOY<dag outs, dag ins, string asmstr, list<dag>
pattern>
 : Instruction {
 field bits<32> Inst;
 let Namespace = "TOY";
 dag OutOperandList = outs;
 dag InOperandList = ins;
 let AsmString = asmstr;
 let Pattern = pattern;
 let Size = 4;
}

def ADDrr : InstTOY<(outs GRRegs:$dst),(ins GRRegs:$src1,
GRRegs:$src2) ... > {
bits<4> src1;
bits<4> src2;
bits<4> dst;
let Inst{31-25} = 0b1100000;
let Inst{24-21} = 0b1100; // Opcode
let Inst{20} = 0b0;
let Inst{19-16} = src1; // Operand 1
let Inst{15-12} = dst; // Destination
let Inst{11-4} = 0b00000000;
let Inst{3-0} = src2;
}


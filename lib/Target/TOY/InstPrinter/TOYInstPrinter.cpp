#include "TOYInstPrinter.h"
#include "TOY.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
using namespace llvm;


void printOperand(const MCInst *MI,
unsigned OpNo, raw_ostream &O) {
 const MCOperand &Op = MI->getOperand(OpNo);
 if (Op.isReg()) {
 printRegName(O, Op.getReg());
 return;
 }
 if (Op.isImm()) {
 O << "#" << Op.getImm();
 return;
 }
 assert(Op.isExpr() && "unknown operand kind in printOperand");
 printExpr(Op.getExpr(), O);
}

/* print the register names */
void printRegName(raw_ostream &OS, unsigned
RegNo) const {
 OS << StringRef(getRegisterName(RegNo)).lower();
}

/* print the instruction */
void printInst(const MCInst *MI,
raw_ostream &O,StringRef Annot) {
 printInstruction(MI, O);
 printAnnotation(O, Annot);
}



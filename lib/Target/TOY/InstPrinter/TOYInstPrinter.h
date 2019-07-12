//= TOYInstPrinter.h - Convert TOY MCInst to asm syntax -------*- C++ -*--//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints a TOY MCInst to a .s file.
//
//===----------------------------------------------------------------------===//
 
#ifndef LLVM_LIB_TARGET_TOY_INSTPRINTER_LANAIINSTPRINTER_H
#define LLVM_LIB_TARGET_TOY_INSTPRINTER_LANAIINSTPRINTER_H

#include "llvm/ADT/StringRef.h"
#include "llvm/MC/MCInstPrinter.h"
namespace llvm{
class TOYInstPrinter : public MCInstPrinter{
public:
TOYInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                    const MCRegisterInfo &MRI)
       : MCInstPrinter(MAI, MII, MRI) {}
void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O,
                     const char *Modifier = nullptr);
void printRegName(raw_ostream &OS, unsigned RegNo) const override;
void printInst(const MCInst *MI, raw_ostream &O, StringRef Annot,
                  const MCSubtargetInfo &STI) override;
};
}
#endif

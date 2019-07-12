#ifndef LLVM_LIB_TARGET_TOY_TOYSUBTARGET_H
#define LLVM_LIB_TARGET_TOY_TOYSUBTARGET_H

#include "TOY.h"
//#include "TOYFrameLowering.h"
//#include "TOYISelLowering.h"
#include "TOYInstrInfo.h"
#include "TOYSelectionDAGInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#define GET_SUBTARGETINFO_HEADER
#include "TOYGenSubtargetInfo.inc"
namespace llvm{
class TOYSubtarget : public TOYGenSubtargetInfo {
 virtual void anchor();
private:
 const DataLayout DL; // Calculates type size & alignment.
 TOYInstrInfo InstrInfo;
 //TOYTargetLowering TLInfo;
 //TOYSelectionDAGInfo TSInfo;
 //TOYFrameLowering FrameLowering;
 //InstrItineraryData InstrItins;
 TOYSubtarget(const std::string &TT, const std::string &CPU,
const std::string &FS, TOYTargetMachine &TM);
 const InstrItineraryData *getInstrItineraryData() const override {
 //return &InstrItins;
}
//const TOYInstrInfo *getInstrInfo() const override { return
//&InstrInfo; }
//const TOYRegisterInfo *getRegisterInfo() const override {
// return &InstrInfo.getRegisterInfo();
//}/*
//const TOYTargetLowering *getTargetLowering() const override {
// return &TLInfo;
//}*/
/*
const TOYFrameLowering *getFrameLowering() const override {
 return &FrameLowering;
}
*//*
const TOYSelectionDAGInfo *getSelectionDAGInfo() const override {
 return &TSInfo;
}*/
/*const DataLayout *getDataLayout() const override { return &DL; }
void ParseSubtargetFeatures(StringRef CPU, StringRef FS);*/


};
} // namespace llvm

#endif 

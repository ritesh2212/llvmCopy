
#include "TOYSubtarget.h"
//#include "Utils/ARMBaseInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetOpcodes.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/IR/Function.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"


using namespace llvm;
// emitPrologue function
void TOYFrameLowering::emitPrologue(MachineFunction &MF)
const {
 const TargetInstrInfo &TII =
*MF.getSubtarget().getInstrInfo();
 MachineBasicBlock &MBB = MF.front();
 MachineBasicBlock::iterator MBBI = MBB.begin();
 DebugLoc dl = MBBI != MBB.end() ? MBBI->getDebugLoc() :
 DebugLoc();
 uint64_t StackSize = computeStackSize(MF);
 if (!StackSize) {
 return;
 }
 unsigned StackReg = TOY::SP;
 unsigned OffsetReg = materializeOffset(MF, MBB, MBBI,
 (unsigned)StackSize);
 if (OffsetReg) {
 BuildMI(MBB, MBBI, dl, TII.get(TOY::SUBrr), StackReg)
 .addReg(StackReg)
 .addReg(OffsetReg)
 .setMIFlag(MachineInstr::FrameSetup);
 } else {
 BuildMI(MBB, MBBI, dl, TII.get(TOY::SUBri), StackReg)
 .addReg(StackReg)
 .addImm(StackSize)
 .setMIFlag(MachineInstr::FrameSetup);
 }
}
// emitEpilog function 
void TOYFrameLowering::emitEpilogue(MachineFunction &MF,
 MachineBasicBlock &MBB)
 const {
 const TargetInstrInfo &TII =
 *MF.getSubtarget().getInstrInfo();
MachineBasicBlock::iterator MBBI =
MBB.getLastNonDebugInstr();
 DebugLoc dl = MBBI->getDebugLoc();
 uint64_t StackSize = computeStackSize(MF);
 if (!StackSize) {
 return;
 }
 unsigned StackReg = TOY::SP;
 unsigned OffsetReg = materializeOffset(MF, MBB, MBBI,
 (unsigned)StackSize);
 if (OffsetReg) {
 BuildMI(MBB, MBBI, dl, TII.get(TOY::ADDrr), StackReg)
 .addReg(StackReg)
 .addReg(OffsetReg)
 .setMIFlag(MachineInstr::FrameSetup);
 } else {
 BuildMI(MBB, MBBI, dl, TII.get(TOY::ADDri), StackReg)
 .addReg(StackReg)
 .addImm(StackSize)
 .setMIFlag(MachineInstr::FrameSetup);
 }
}
/* helper function used to determine offset for the ADD stack operation */

static unsigned materializeOffset(MachineFunction &MF,
MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
unsigned Offset) {
 const TargetInstrInfo &TII =
 *MF.getSubtarget().getInstrInfo();
 DebugLoc dl = MBBI != MBB.end() ? MBBI->getDebugLoc() :
 DebugLoc();
 const uint64_t MaxSubImm = 0xfff;
 if (Offset <= MaxSubImm) {
 return 0;
 } else {
 unsigned OffsetReg = TOY::R2;
 unsigned OffsetLo = (unsigned)(Offset & 0xffff);
 unsigned OffsetHi = (unsigned)((Offset & 0xffff0000) >>
 16);
 BuildMI(MBB, MBBI, dl, TII.get(TOY::MOVLOi16),
 OffsetReg)
 .addImm(OffsetLo)
 .setMIFlag(MachineInstr::FrameSetup);
 if (OffsetHi) {
 BuildMI(MBB, MBBI, dl, TII.get(TOY::MOVHIi16),
 OffsetReg)
 .addReg(OffsetReg)
 .addImm(OffsetHi)
 .setMIFlag(MachineInstr::FrameSetup);
 }
 return OffsetReg;
 }
}


/*  more helper functions used to compute the stack size */

uint64_t TOYFrameLowering::computeStackSize(MachineFunction
&MF) const {
 MachineFrameInfo *MFI = MF.getFrameInfo();
 uint64_t StackSize = MFI->getStackSize();
 unsigned StackAlign = getStackAlignment();
 if (StackAlign > 0) {
 StackSize = RoundUpToAlignment(StackSize, StackAlign);
 }
 return StackSize;
}



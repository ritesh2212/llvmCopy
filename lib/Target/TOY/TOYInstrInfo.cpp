#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
bool
expandPostRAPseudo(MachineBasicBlock::iterato
r MI) const {
 if (MI->getOpcode() == TOY::MOVi32){
 DebugLoc DL = MI->getDebugLoc();
 MachineBasicBlock &MBB = *MI->getParent();
 const unsigned DstReg = MI->getOperand(0).getReg();
 const bool DstIsDead = MI->getOperand(0).isDead();
 const MachineOperand &MO = MI->getOperand(1);
 auto LO16 = BuildMI(MBB, MI, DL, get(TOY::MOVLOi16),
 DstReg);
 auto HI16 = BuildMI(MBB, MI, DL, get(TOY::MOVHIi16))
 .addReg(DstReg, RegState::Define |
 getDeadRegState(DstIsDead))
 .addReg(DstReg);
 MBB.erase(MI);
 return true;
 }
}

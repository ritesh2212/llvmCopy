//===-- Cpu0MCTargetDesc.cpp - Cpu0 Target Descriptions -------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Cpu0 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "Cpu0MCTargetDesc.h"
#include "llvm/MC/MachineLocation.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"
#include <cstdint>
#include <string>

using namespace llvm;

//Target llvm::TheCpu0Target;

#define GET_INSTRINFO_MC_DESC
#include "Cpu0GenInstrInfo.inc"


#define GET_SUBTARGETINFO_MC_DESC
#include "Cpu0GenSubtargetInfo.inc"


#define GET_REGINFO_MC_DESC
#include "Cpu0GenRegisterInfo.inc"
//@2 {


static MCInstrInfo *createCpu0MCInstrInfo() {
	MCInstrInfo *X = new MCInstrInfo();
    	InitCpu0MCInstrInfo(X);
   	return X;
}

static MCRegisterInfo *createCpu0MCRegisterInfo(const Triple & /*TT*/) {
    MCRegisterInfo *X = new MCRegisterInfo();
    InitCpu0MCRegisterInfo(X, Cpu0::RA, 0, 0, Cpu0::PC);
    return X;
  }
  
  static MCSubtargetInfo *
  createCpu0MCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
    std::string CPUName = CPU;
    if (CPUName.empty())
      CPUName = "generic";
  
    return createCpu0MCSubtargetInfoImpl(TT, CPUName, FS);
 }
  



extern "C" void LLVMInitializeCpu0TargetMC() {
	
	// Register the MC instruction info.
	TargetRegistry::RegisterMCInstrInfo(getTheCpu0Target(),
                                       createCpu0MCInstrInfo);

	// Register the MC register info.
	TargetRegistry::RegisterMCRegInfo(getTheCpu0Target(),
	                                createCpu0MCRegisterInfo);

	// Register the MC subtarget info.
	TargetRegistry::RegisterMCSubtargetInfo(getTheCpu0Target(),
                                           createCpu0MCSubtargetInfo);

}
//@2 }


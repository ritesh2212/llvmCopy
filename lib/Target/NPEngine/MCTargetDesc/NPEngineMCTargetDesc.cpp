#include "NPEngineMCTargetDesc.h"
//#include "InstrPrinter/NPEngineInstPrinter.h"
//#include "NPEngineMCASMInfo.h"
//#include "llvm/MC/MCCodeGenInfo.h"  -- not found in llvm 8
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
//#include "llvm/Support/FormattedStream.h" -- not found in llvm 8
#include "llvm/Support/TargetRegistry.h"
/*
#define GET_INSTRINFO_MC_DESC
#include "NPEngineGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "NPEngineGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "NPEngineGenRegisterInfo.inc"
*/
using namespace llvm;

static MCInstrInfo *createNPEngineInstrInfo(){
	MCInstrInfo *X = new MCInstrInfo();
	InitNPEngineMCInstrInfo(X);
	return X;
}

static MCRegisterInfo *createNPEngineMCRegisterInfo(StringRef TT){
	MCRegisterInfo * X = new MCRegisterInfo();
	InitNPEngineMCRegisterInfo(X, NPEngine:: LR);
	return X;
}	

static MCSubtargetInfo *createNPEngineMCSubtargetInfo(
		StringRef TT, 
		StringRef CPU, 
		StringRef FS){
	MCSubtargetInfo *X = new MCSubtargetInfo();
	InitNPEngineMCSubtargetInfo(X, TT, CPU, FS);
	return X;
}

static MCASMInfo *createNPEngineMCASMInfo(const
		MCRegisterInfo &MRI,
		StringRef TT){
	MCASMInfo *MAI= new NPEngineMCASMInfo(TT);
	return MAI;
}

static MCCodeGenInfo *createNPEngineMCCdoeGenInfo(
		StringRef TT,
		Reloc::Model RM,
		CodeModel::Model CM,
		CodeGenOpt::Level OL){
	MCCodeGenInfo *X = new MCCodeGenInfo();
	if(RM== Reloc::Default){
		RM = Reloc::Static;
	}
	if(CM== CodeModel::Default){
		CM = CodeModel::Small;
	}
	if(CM!=CodeModel::Small && CM!=CodeModel::Large){
		report_fatal_error("Target only supports CodeModel Small or Large");
	}
	X->InitMCCodeGenInfo(RM, CM, OL);
	return X;
}

static MCInstrPrinter *createNPEngineMCInstrPrinter(const
		Target &T,
		unsigned SyntaxVariant, const
		MCASMInfo &MAI, const
		MCInstrInfo &MII, const
		MCRegisterInfo &MRI, const
		MCSubtargetInfo &STI){
		return new NPEngineInstrPrinter(MAI, MII, MRI);
}

static MCStreamer *createMCASMStreamer(
		MCContext &Ctx,
		formatted_raw_ostream &OS,
		bool isVerboseASM,
		bool useDwarfDirectory,
		MCInstPrinter *InstPrint,
		MCCodeEmitter *CE,
		MCASMBackend *TAB,
		bool ShowInst){
		return createASMStreamer(Ctx, OS, isVerboeASM, useDwarfDirectory, InstPrint, CE, TAB, ShowInst);
}

static MCStreamer *createMCStreamer(const
		Target &T,
		StringRef TT,
		MCContext &Ctx,
		MCASMBackend &MAB,
		raw_ostream &OS,
		MCCodeEmitter *Emitter,const
		MCSubtargetInfo &STI,
		bool RelaxAll,
		bool NoExecStack){
	return createELFStreamer(Ctx, MAB, OS, Emitter, false, NoExecStack);
}

//Force static initialization

extern "C" void LLVMInitializeNPEngineTargetMC(){
	
	//Register the MCASMInfo
	RegisterMCASMInfoFn X(
			TheNPEngineTarget, 
			createNPEngineMCASMInfo
			);

	//Register MCCodegen info
	Targetregistry::RegisterMCCodeGenInfo(
			TheNPEngineTarget, 
			createNPEngineMCCodeGenInfo
			);

	//Register the MC instruction info
	TargetRegistry::RegisterMCInstrInfo(
			TheNPEngineTarget,
			createNPENgineMCInstrInfo
			);

	//Register the MC register info
	TargetRegistry::RegisterMCRegInfo(
			TheNPEngineTarget,
			createNPEngineMCRegisterInfo
			);

	//Register MCSubtargetInfo
	TargetRegistry::RegisterMCSubtargetInfo(
			TheNPEngineTarget,
			createNPEngineMCSubtargetInfo
			);
	
	//Register MCInstPrinter
	TargetRegistry::RegisterMCInstPrinter(
			TheNPEngineTarget,
			createNPEngineMCInstPrinter
			);

	//Register ASMBackend
	TargetRegistry::RegisterASMBackend(
			TheNPEngineTarget,
			createNPEngineASMBackend
			);
	
	//Register the assembly streamer
	TargetRegistry::RegisterASMStreamer(
			TheNPEngineTarget,
			createMCStreamer
			);

	// Register the MC Code Emitter
	TargetRegistry::RegisterMCCodeEmitter(
			TheNPEngineTarget,
			createNPEngineMCCodeEmitter
			);

}




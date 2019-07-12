#include "NPEngineTargetMachine.h"
#include "NPEngine.h"
//#include "NPEngineFrameLowering.h"
//#include "NPEngineInstrInfo.h"
//#include "NPEngineISelLowering.h"
//#include "NPEngineSelectionDAGInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;
NPEngineTargetMachine::NPEngineTargetMachine(const Target &T, StringRef TT, StringRef CPU, StringRef FS, 
		const TargetOptions &Options, Reloc::Model RM, CodeModel::Model CM, CodeGenOpt::Level OL ):LLVMTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL)//,
	//Subtarget(TT, CPU, FS, *this) --
	{
		initASMInfo();
	}

namespace{
	class NPEnginePassConfig : public TargetPassConfig{
		public:
		       NPEnginePassConfig(NPEngineTargetMachine *TM, PassManagerBase &PM) : TargetPassConfig(TM,PM){
		       }
	       	       NPEngineTargetMachine & getNPEngineTargetMachine() const{
		       		return getTM<NPEngineTargetMachine>();
		       }
			       
			virtual bool addPreISel();
			virtual bool addInstrSelector();
			virtual bool addPreEmitPass();

	};
} // closing of namespace

TargetPassConfig *NPEngineTargetMachine::createPassConfig(PassManagerBase &PM){
	return new NPEnginePassConfig(this, PM);
}

bool NPEnginePassConfig::addPreISel(){
	return false;
}

bool NPEnginePassConfig::addInstrSelector(){
	addPass(createNPEngineISelDAG(getNPEngineTargetMachine(),getOptLevel()));
	return false;
}

bool NPEnginePassConfig::addPreEmitPass(){
	return false;
}


// Force Static Initialization.

extern "C" void LLVMInitializeNPEngineTarget(){
	RegisterTargetMachine<NPEngineTargetMachine> X(TheNPEngineTarget);
}

void NPEngineTargetMachine::addAnalysisPasses(PassManagerBase &PM){}


#ifndef TARGET_NPEngine_H
#define TARGET_NPEngine_H

#include "MCTargetDesc/NPEngineMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm
{
	class TargetMachine;
	class NPEngineTargetMachine;
	FunctionPass *createNPEngineISelDag(NPEngineTargetMachine & TM, CodeGenOpt::Level OptLevel);
}//end namespace llvm; 
#endif


//#include "NPEngine.h"
//#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;
Target llvm::TheNPEngineTarget;
namespace llvm{
extern "C" void LLVMInitializeNPEngineTargetInfo(){
	RegisterTarget<Triple::NPEngine> X(TheNPEngineTarget, "NPEngine", "NPEngine","NPEngine");
}
}

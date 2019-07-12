#include "TOYInstrInfo.h"
#include "TOYSubtarget.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"
const TOYInstrInfo *getInstrInfo() const override {
return getSubtargetImpl()->getInstrInfo();
}

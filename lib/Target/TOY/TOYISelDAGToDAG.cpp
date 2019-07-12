#include "TOY.h"
#include "TOYTargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
//#include "TOYInstrInfo.h"

using namespace llvm;
class TOYDAGToDAGISel : public SelectionDAGISel {
 const TOYSubtarget &Subtarget;
public:
 explicit TOYDAGToDAGISel(TOYTargetMachine &TM,
 CodeGenOpt::Level OptLevel)
: SelectionDAGISel(TM, OptLevel), Subtarget(*TM.
getSubtargetImpl()) {}
SDNode *Select(SDNode *N);
bool SelectAddr(SDValue Addr, SDValue &Base, SDValue
 &Offset);
};

SDNode *TOYDAGToDAGISel::Select(SDNode *N) {
 return SelectCode(N);
}

bool TOYDAGToDAGISel::SelectAddr(SDValue Addr, SDValue
&Base, SDValue &Offset) {
 if (FrameIndexSDNode *FIN =
dyn_cast<FrameIndexSDNode>(Addr)) {
 Base = CurDAG->getTargetFrameIndex(FIN->getIndex(),
 getTargetLowering()-
 >getPointerTy());
 Offset = CurDAG->getTargetConstant(0, MVT::i32);
 return true;
 }
 if (Addr.getOpcode() == ISD::TargetExternalSymbol ||
 Addr.getOpcode() == ISD::TargetGlobalAddress ||
 Addr.getOpcode() == ISD::TargetGlobalTLSAddress) {
 return false; // direct calls.
 }
 Base = Addr;
 Offset = CurDAG->getTargetConstant(0, MVT::i32);
 return true;
}

FunctionPass *llvm::createTOYISelDag(TOYTargetMachine &TM,
CodeGenOpt::Level OptLevel) {
return new TOYDAGToDAGISel(TM, OptLevel);
}


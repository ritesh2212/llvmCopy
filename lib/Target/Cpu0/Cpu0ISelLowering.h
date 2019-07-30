#ifndef LLVM_LIB_TARGET_CPU0_CPU0ISELLOWERING_H
#define LLVM_LIB_TARGET_CPU0_CPU0ISELLOWERING_H
#include "Cpu0.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/IR/Function.h"
#include "llvm/CodeGen/TargetLowering.h"
#include <deque>
namespace llvm{
class Cpu0Subtarget;
class Cpu0TargetLowering : public TargetLowering  
{
    public:

 //  	 explicit Cpu0TargetLowering(const Cpu0TargetMachine &TM,
   //                             const Cpu0Subtarget &STI);
    
    //	static const Cpu0TargetLowering *create(const Cpu0TargetMachine &TM,
      //                                      const Cpu0Subtarget &STI);
    
    
//    	SDValue PerformDAGCombine(SDNode *N, DAGCombinerInfo &DCI) const override;
	
   protected:
       const Cpu0Subtarget &Subtarget;
    // Cache the ABI from the TargetMachine, we use it everywhere.
//    const Cpu0ABIInfo &ABI;
    struct ByValArgInfo {
      unsigned FirstIdx; // Index of the first register used.
      unsigned NumRegs;  // Number of registers used for this argument.
      unsigned Address;  // Offset of the stack area used to pass this argument.

      ByValArgInfo() : FirstIdx(0), NumRegs(0), Address(0) {}
    };

};
}
#endif

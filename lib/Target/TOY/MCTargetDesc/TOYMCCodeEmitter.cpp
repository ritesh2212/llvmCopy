#include "TOY.h"
#include "llvm/ADT/SmallVector.h"
 #include "llvm/ADT/Statistic.h"
 #include "llvm/MC/MCCodeEmitter.h"
 #include "llvm/MC/MCExpr.h"
 #include "llvm/MC/MCFixup.h"
 #include "llvm/MC/MCInst.h"
 #include "llvm/MC/MCInstrInfo.h"
 #include "llvm/MC/MCRegisterInfo.h"
 #include "llvm/MC/MCSubtargetInfo.h"
 #include "llvm/Support/Casting.h"
 #include "llvm/Support/raw_ostream.h"
 #include <cassert>
 #include <cstdint>







unsigned getMachineOpValue(const 
		MCInst &MI,const
 		MCOperand &MO,
		SmallVectorImpl<MCFixup> &Fixups,const
 		MCSubtargetInfo &STI) const{
 			if (MO.isReg()) {
 				return CTX.getRegisterInfo()->getEncodingValue(MO.getReg());
 			}
                }
void EncodeInstruction(const 
		MCInst &MI,
		raw_ostream &OS, 
		SmallVectorImpl<MCFixup> &Fixups, const
		MCSubtargetInfo &STI) const{
 			const MCInstrDesc &Desc = MCII.get(MI.getOpcode());
 			if (Desc.getSize() != 4) {
 				llvm_unreachable("Unexpected instruction size!");
 			}
 			const uint32_t Binary = getBinaryCodeForInstr(MI,Fixups, STI);
 			EmitConstant(Binary, Desc.getSize(), OS);
 			++MCNumEmitted;
		}


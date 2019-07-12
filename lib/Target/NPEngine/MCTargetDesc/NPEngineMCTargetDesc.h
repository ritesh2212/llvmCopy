#ifndef NPEngineMCTARGETDESC_H
#define NPEngineMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm{
	class Target;
	class MCInstrInfo;
	class MCRegisterInfo;
	class MCSubtargetInfo;
	class MCContext;
	class MCCodeEmitter;
	class MCASMInfo;
	class MCCodeGenInfo;
	class MCInstPrinter;
	class MCObjectWriter;
	class MCASMBackend;
	class StringRef;
	class raw_ostream;
	extern Target TheNPEngineTarget;
	MCCodeEmitter *createNPEngineMCCodeEmitter(const 
			MCInstrInfo &MCII, const
			MCRegisterInfo &MRI, const
			MCSubtargetInfo &STI,
			MCContext &Ctx);
	MCASMBackend *createNPEngineASMBackend(const
			Target &T, const
			MCRegisterInfo &MRI,
			StringRef TT,
			StringRef CPU
			);
	MCObjectWriter *createNPEngineELFObjectWriter( 
			raw_ostream &OS,
			uint8_t OSABI
			);

}    // End of LLVM namespace
/*
#define GET_REGINFO_ENUM
#include "NPEngineGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "NPEngineGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "NPEngineGenSubtargetInfo.inc"
*/
#endif

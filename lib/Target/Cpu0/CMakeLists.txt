set(LLVM_TARGET_DEFINITIONS Cpu0.td)

tablegen(LLVM Cpu0GenRegisterInfo.inc -gen-register-info) 
tablegen(LLVM Cpu0GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM Cpu0GenSubtargetInfo.inc -gen-subtarget)
add_public_tablegen_target(Cpu0CommonTableGen)
add_llvm_target(Cpu0CodeGen
         Cpu0TargetMachine.cpp
         Cpu0ISelDAGToDAG.cpp 
	 Cpu0RegisterInfo.cpp
	 Cpu0FrameLowering.cpp
	 Cpu0Subtarget.cpp
	 Cpu0InstrInfo.cpp
         Cpu0TargetObjectFile.cpp
         Cpu0ISelLowering.cpp
	)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)


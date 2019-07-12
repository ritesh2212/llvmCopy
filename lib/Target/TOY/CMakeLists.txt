set(LLVM_TARGET_DEFINITIONS TOY.td)

tablegen(LLVM TOYGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM TOYGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TOYGenSubtargetInfo.inc -gen-subtarget)

tablegen(LLVM TOYGenDAGISel.inc -gen-dag-isel)


add_public_tablegen_target(TOYCommonTableGen)



add_llvm_target(TOYCodeGen
	TOYISelDAGToDAG.cpp
	TOYFrameLowering.cpp
	TOYTargetMachine.cpp
	TOYSubtarget.cpp
	TOYInstrInfo.cpp
	)


add_subdirectory(InstPrinter)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)

Target llvm::TheBARETarget;

extern "C" void LLVMInitializeBARETargetInfo() {
        RegisterTarget<> X(TheBARETarget, "BARE", "BARE");
}


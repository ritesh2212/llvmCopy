extern "C" void LLVMInitializeBARETargetInfo() {
    RegisterTarget<Triple::UnknownArch> X(TheBARETarget, "BARE", "BARE");
}

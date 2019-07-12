extern "C" void LLVMInitializeBAREAsmPrinter() {
    RegisterAsmPrinter<BAREAsmPrinter> X(TheBARETarget);
}

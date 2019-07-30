//===--- Cpu0.cpp - Implement Cpu0 target feature support --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements Cpu0 TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "Cpu0.h"
#include "clang/Basic/MacroBuilder.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;

const char *const Cpu0TargetInfo::GCCRegNames[] = {
    "r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",  "r8",  "r9",  "r10",
    "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19", "r20", "r21",
    "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31"
};

ArrayRef<const char *> Cpu0TargetInfo::getGCCRegNames() const {
  return llvm::makeArrayRef(GCCRegNames);
}

const TargetInfo::GCCRegAlias Cpu0TargetInfo::GCCRegAliases[] = {
    {{"pc"}, "r2"},   {{"sp"}, "r4"},   {{"fp"}, "r5"},   {{"rv"}, "r8"},
    {{"rr1"}, "r10"}, {{"rr2"}, "r11"}, {{"rca"}, "r15"},
};

ArrayRef<TargetInfo::GCCRegAlias> Cpu0TargetInfo::getGCCRegAliases() const {
  return llvm::makeArrayRef(GCCRegAliases);
}

bool Cpu0TargetInfo::isValidCPUName(StringRef Name) const {
  return llvm::StringSwitch<bool>(Name).Case("v11", true).Default(false);
}
void Cpu0TargetInfo::fillValidCPUList(
    SmallVectorImpl<StringRef> &Values) const {
  Values.emplace_back("v11");
}

bool Cpu0TargetInfo::setCPU(const std::string &Name) {
  CPU = llvm::StringSwitch<CPUKind>(Name).Case("v11", CK_V11).Default(CK_NONE);

  return CPU != CK_NONE;
}

bool Cpu0TargetInfo::hasFeature(StringRef Feature) const {
  return llvm::StringSwitch<bool>(Feature).Case("cpu0", true).Default(false);
}

void Cpu0TargetInfo::getTargetDefines(const LangOptions &Opts,
                                       MacroBuilder &Builder) const
  {
   // Define __cpu0__ when building for target cpu0.
  Builder.defineMacro("__cpu0__");

  // Set define for the CPU specified.
  switch (CPU) {
  case CK_V11:
    Builder.defineMacro("__CPU0_V11__");
    break;
  case CK_NONE:
    llvm_unreachable("Unhandled target CPU");
  }
}

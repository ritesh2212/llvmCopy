//===-- Cpu0ISelDAGToDAG.h -----------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// Cpu0 specific code to select Cpu0 machine instructions for
// SelectionDAG operations.
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Cpu0_Cpu0ISELDAGTODAG_H
#define LLVM_LIB_TARGET_Cpu0_Cpu0ISELDAGTODAG_H

#include "Cpu0TargetMachine.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/Support/CodeGen.h"

#include <vector>

namespace llvm {

class Cpu0DAGToDAGISel : public SelectionDAGISel {

public:
	explicit Cpu0DAGToDAGISel(Cpu0TargetMachine &tm)
	      : SelectionDAGISel(tm) {}
      
	void Select(SDNode *N) override;      
  

}; // end Cpu0DAGToDAGISel
}

#endif // LLVM_LIB_TARGET_Cpu0_Cpu0ISELDAGTODAG_H

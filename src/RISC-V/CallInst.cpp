#include "CallInst.h"
#include "IR/IRType.h"
#include "Value.h"

namespace RISCV {
    CallInst::CallInst(Function *F, BasicBlock *parent)
        : Instruction(IRType::VoidTy, Call, parent) {
        Operands.push_back(new Value(F));
    }

    void CallInst::print(std::ostream &O) const {
        O << "call ";
        Operands[0]->print(O);
        O << std::endl;
    }
} // RISCV
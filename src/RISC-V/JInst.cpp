#include "JInst.h"
#include "IR/IRType.h"
#include "BasicBlock.h"
#include "Value.h"

namespace RISCV {
    JInst::JInst(BasicBlock *dest, BasicBlock *parent) : Instruction(IRType::VoidTy, J, parent) {
        Operands.push_back(new Value(dest));
    }

    void JInst::print(std::ostream &O) const {
        O << "j ";
        Operands[0]->print(O);
        O << std::endl;
    }
} // RISCV
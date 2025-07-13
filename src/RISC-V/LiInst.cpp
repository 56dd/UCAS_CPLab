#include "LiInst.h"
#include "IR/IRType.h"
#include "Value.h"

namespace RISCV {
    LiInst::LiInst(Value *rd, int val, BasicBlock *parent) : Instruction(IRType::VoidTy, Li, parent) {
        Operands.push_back(rd);
        Operands.push_back(new Value(val));
    }

    void LiInst::print(std::ostream &O) const {
        O << "li ";
        Operands[0]->print(O);
        O << ", ";
        Operands[1]->print(O);
        O << std::endl;
    }


} // RISCV
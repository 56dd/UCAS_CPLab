#include "ReturnInst.h"
#include "IR/IRType.h"


namespace RISCV {
    ReturnInst::ReturnInst(BasicBlock *parent) : Instruction(IRType::VoidTy, Instruction::Ret, parent) {

    }

    void ReturnInst::print(std::ostream &O) const {
        O << "ret" << std::endl;
    }
} // RISCV
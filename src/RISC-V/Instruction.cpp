#include "Instruction.h"
#include "BasicBlock.h"

namespace RISCV {
    Instruction::Instruction(IRType *Ty, unsigned int iType, BasicBlock *parent) : ty(Ty), iType(iType), parent(parent) {
        if (parent) {
            parent->addInstruction(this);
        }
    }
} // RISCV
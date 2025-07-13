#ifndef COMPILER_SETCONDINST_H
#define COMPILER_SETCONDINST_H

#include "Instruction.h"

class Value;

namespace RISCV {

    class SetCondInst : public Instruction {
    public:
        SetCondInst(unsigned iType, Value *rd, Value *op1, Value *op2, BasicBlock *parent = nullptr);

        void print(std::ostream &O) const override;
    };

} // RISCV

#endif //COMPILER_SETCONDINST_H

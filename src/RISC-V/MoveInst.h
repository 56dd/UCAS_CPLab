#ifndef COMPILER_MOVEINST_H
#define COMPILER_MOVEINST_H

#include "Instruction.h"

namespace RISCV {

    class MoveInst : public Instruction {
    private:
        IRType *ty;
    public:
        MoveInst(IRType *ty, Value *dest, Value *src, BasicBlock *parent = nullptr);

        void print(std::ostream &O) const override;
    };

} // RISCV

#endif //COMPILER_MOVEINST_H

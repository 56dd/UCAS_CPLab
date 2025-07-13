#ifndef COMPILER_LIINST_H
#define COMPILER_LIINST_H

#include "Instruction.h"

namespace RISCV {

    class LiInst : public Instruction {
    public:
        LiInst(Value *rd, int val, BasicBlock *parent = nullptr);

        void print(std::ostream &O) const override;
    };

} // RISCV

#endif //COMPILER_LIINST_H

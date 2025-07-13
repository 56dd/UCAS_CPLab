#ifndef COMPILER_JINST_H
#define COMPILER_JINST_H

#include "Instruction.h"

namespace RISCV {

    class JInst : public Instruction {
    public:
        explicit JInst(BasicBlock *dest, BasicBlock *parent = nullptr);

        void print(std::ostream &O) const override;
    };

} // RISCV

#endif //COMPILER_JINST_H

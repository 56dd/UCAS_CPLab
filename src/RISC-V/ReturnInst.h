#ifndef COMPILER_RETURNINST_H
#define COMPILER_RETURNINST_H

#include "Instruction.h"

namespace RISCV {

    class ReturnInst : public Instruction {
    public:
        explicit ReturnInst(BasicBlock *parent = nullptr);

        void print(std::ostream &O) const override;
    };

} // RISCV

#endif //COMPILER_RETURNINST_H

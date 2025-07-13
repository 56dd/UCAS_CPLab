#ifndef COMPILER_CALLINST_H
#define COMPILER_CALLINST_H

#include "Instruction.h"

namespace RISCV {

    class Function;

    class CallInst : public Instruction {
    public:
        explicit CallInst(Function *F, BasicBlock *parent = nullptr);

        void print(std::ostream &O) const override;
    };

} // RISCV

#endif //COMPILER_CALLINST_H

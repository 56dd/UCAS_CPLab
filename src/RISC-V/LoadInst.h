#ifndef COMPILER_LOADINST_H
#define COMPILER_LOADINST_H

#include "Instruction.h"

#include "Value.h"

namespace RISCV {

    class LoadInst : public Instruction {
        Value *rt;
    public:
        LoadInst(Value *rd, Pointer *ptr, BasicBlock *parent = nullptr, IRType *ty = nullptr, Value *rt = nullptr);

        void print(std::ostream &O) const override;
    };

} // RISCV

#endif //COMPILER_LOADINST_H

#ifndef COMPILER_INSTRUCTION_H
#define COMPILER_INSTRUCTION_H

#include "User.h"

#include <iostream>

class IRType;

namespace RISCV {

    class BasicBlock;

    class Instruction : public User {
    private:
        BasicBlock *parent;
        IRType *ty;

    protected:
        unsigned iType;

        Instruction(IRType *Ty, unsigned iType, BasicBlock *parent = nullptr);

    public:
        virtual void print(std::ostream &O) const = 0;

        enum TermOps {
#define FIRST_TERM_INST(N) TermOpsBegin = N,
#define HANDLE_TERM_INST(N, OPC, CLASS) OPC = N,
#define LAST_TERM_INST(N) TermOpsEnd = N + 1,

#include "Instruction.def"
        };

        enum BinaryOps {
#define FIRST_BINARY_INST(N) BinaryOpsBegin = N,
#define HANDLE_BINARY_INST(N, OPC, CLASS) OPC = N,
#define LAST_BINARY_INST(N) BinaryOpsEnd = N + 1,

#include "Instruction.def"
        };

        enum MemoryOps {
#define FIRST_MEMORY_INST(N) MemoryOpsBegin = N,
#define HANDLE_MEMORY_INST(N, OPC, CLASS) OPC = N,
#define LAST_MEMORY_INST(N) MemoryOpsEnd = N + 1,

#include "Instruction.def"
        };

        enum OtherOps {
#define FIRST_OTHER_INST(N) OtherOpsBegin = N,
#define HANDLE_OTHER_INST(N, OPC, CLASS) OPC = N,
#define LAST_OTHER_INST(N) OtherOpsEnd = N + 1,

#include "Instruction.def"
        };
    };

} // RISCV

#endif //COMPILER_INSTRUCTION_H

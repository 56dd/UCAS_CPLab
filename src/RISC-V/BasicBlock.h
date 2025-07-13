#ifndef COMPILER_BASICBLOCK_H
#define COMPILER_BASICBLOCK_H

#include <iostream>
#include <vector>

class IRBasicBlock;

namespace RISCV {

    class Instruction;

    class Function;

    class BasicBlock {
    private:
        std::vector<Instruction *> InstList;
        Function *parent;
        std::string name;
        IRBasicBlock *irBasicBlock;
    public:
        BasicBlock(IRBasicBlock *irBasicBlock, Function *parent);

        void addInstruction(Instruction *inst);

        void generate();

        void setName(const std::string &name);

        const std::string &getName() const;

        void print(std::ostream &O);

        const std::vector<Instruction *> &getInstList() const;

        IRBasicBlock *getIrBb() const;
    };

} // RISCV

#endif //COMPILER_BASICBLOCK_H

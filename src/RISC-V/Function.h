#ifndef COMPILER_FUNCTION_H
#define COMPILER_FUNCTION_H

#include <string>
#include <vector>
#include <map>
#include "Environment.h"
#include "IR/IRBasicBlock.h"

class IRFunction;

namespace RISCV {

    class Module;

    class BasicBlock;

    class Pointer;

    class Function {
    private:
        std::string name;
        Module *parent;
        std::vector<BasicBlock *> BasicBlockList;
        std::map<IRBasicBlock *, BasicBlock *> BasicBlockSet;
        Section section;
        unsigned align;
        BasicBlock *entryBlock;

        void generateEntryBlock();

        IRFunction *irFunction;

        unsigned allocSize = 0;

        std::map<IRAllocaInst *, Pointer *> allocPtrMap;

        std::map<Register *, Pointer *> regPtrMap;

    public:
        explicit Function(IRFunction *irFunc, Module *parent = nullptr);

        explicit Function(std::string name);

        BasicBlock *getNextBlock(BasicBlock *block);

        void addBasicBlock(BasicBlock *BB);

        Module *getParent() const;

        void print(std::ostream &O);

        Pointer *getPointer(IRAllocaInst *alloc);

        Pointer *getPointer(Register *reg);

        BasicBlock *findBasicBlock(IRBasicBlock *irBasicBlock);

        const std::string &getName() const;

        static int alignSize(unsigned long i);

        IRFunction *getIrFunction() const;

        unsigned int getAllocSize() const;
    };

} // RISCV

#endif //COMPILER_FUNCTION_H

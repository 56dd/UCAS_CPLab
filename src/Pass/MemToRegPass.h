#ifndef COMPILER_MEMTOREGPASS_H
#define COMPILER_MEMTOREGPASS_H

#include <stack>
#include "Pass.h"
#include "IR/iMemory.h"
#include "utils/DominatorTree.h"

class DominatorTree;

class MemToRegPass : public FunctionPass {
public:
    explicit MemToRegPass(std::string name = "", int level = 1);

    void runOnFunction(IRFunction &F) override;

private:
    static bool isAllocaPromotable(IRAllocaInst *AI);

    static void mem2reg(std::vector<IRAllocaInst *> Allocs, DominatorTree *root, std::vector<IRBasicBlock *> &BBList,
                        ControlFlowGraph *cfg);

    static void renamePass(DominatorTree *node, IRAllocaInst *alloc, std::vector<IRInstruction *> *bin,
                           std::stack<IRValue *> *valueStack);

};


#endif //COMPILER_MEMTOREGPASS_H

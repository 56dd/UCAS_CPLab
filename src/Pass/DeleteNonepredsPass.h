#ifndef COMPILER_DELETENONEPREDSPASS_H
#define COMPILER_DELETENONEPREDSPASS_H

#include "Pass.h"

class DeleteNonePredsPass : public FunctionPass {
public:
    explicit DeleteNonePredsPass(std::string name = "", int level = 0);

    void runOnFunction(IRFunction &F) override;

private:
    static void dfs(IRBasicBlock *block, ControlFlowGraph *G, std::map<IRBasicBlock *, bool> &visited);
};

#endif //COMPILER_DELETEPREDSNONEPASS_H

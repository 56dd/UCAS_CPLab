#ifndef COMPILER_AGGRESSIVEDEADCODEELIMINATEPASS_H
#define COMPILER_AGGRESSIVEDEADCODEELIMINATEPASS_H

#include <queue>
#include "Pass.h"

class AggressiveDeadCodeEliminatePass : public FunctionPass {
public:
    explicit AggressiveDeadCodeEliminatePass(std::string name = "", int level = 1);

    void runOnFunction(IRFunction &F) override;

    static void initWorkList(IRFunction *F, std::queue<IRInstruction *> *Queue,
                             std::set<IRInstruction *> *activeInstSet,
                             std::set<IRBasicBlock *> *activeBlockSet);

    static bool isNaturalActiveInst(IRInstruction *inst);
};


#endif //COMPILER_AGGRESSIVEDEADCODEELIMINATEPASS_H

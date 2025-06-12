#ifndef COMPILER_STRENGTHREDUCTIONPASS_H
#define COMPILER_STRENGTHREDUCTIONPASS_H

#include "Pass.h"
#include "utils/LoopInfo.h"
#include "utils/BasicInductionVariable.h"

class StrengthReductionPass : public FunctionPass {
public:
    explicit StrengthReductionPass(std::string name = "", int level = 2);

    void runOnFunction(IRFunction &F) override;

private:
    static bool reduction(IRFunction *F, BasicInductionVariable *const &BI, LoopInfo *loop,
                          std::set<BasicInductionVariable *> *BISet);

    static IRBinaryOperator *findInductionVarUsePhi(BasicInductionVariable *const &BI, LoopInfo *loop);

    static IRBinaryOperator *findInductionVarUseCalc(BasicInductionVariable *const &BI, LoopInfo *loop);
};


#endif //COMPILER_STRENGTHREDUCTIONPASS_H

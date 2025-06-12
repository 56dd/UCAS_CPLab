#ifndef COMPILER_ELIMINATEBASICINDUCTIONVARPASS_H
#define COMPILER_ELIMINATEBASICINDUCTIONVARPASS_H

#include "Pass.h"

class EliminateBasicInductionVarPass : public FunctionPass {
public:
    explicit EliminateBasicInductionVarPass(std::string name = "", int level = 2);

    void runOnFunction(IRFunction &F) override;
};


#endif //COMPILER_ELIMINATEBASICINDUCTIONVARPASS_H

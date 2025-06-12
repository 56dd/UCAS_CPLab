#ifndef COMPILER_CONSTANTPASS_H
#define COMPILER_CONSTANTPASS_H

#include "Pass.h"

class ConstantPass : public BasicBlockPass {
public:
    explicit ConstantPass(std::string name = "", int level = 0);

    void runOnBasicBlock(IRBasicBlock &BB) override;
};


#endif //COMPILER_CUTDEADBLOCKPASS_H

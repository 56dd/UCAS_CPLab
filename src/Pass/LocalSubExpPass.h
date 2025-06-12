#ifndef COMPILER_LOCALSUBEXPPASS_H
#define COMPILER_LOCALSUBEXPPASS_H

#include "Pass.h"

class LocalSubExpPass : public BasicBlockPass {
public:
    explicit LocalSubExpPass(std::string name = "", int level = 1);

    void runOnBasicBlock(IRBasicBlock &BB) override;
};


#endif //COMPILER_RENAMEPASS_H

#ifndef COMPILER_REGISTERPASS_H
#define COMPILER_REGISTERPASS_H

#include "Pass.h"
#include "utils/RegisterNode.h"

class RegisterPass : public FunctionPass {
public:
    explicit RegisterPass(std::string name = "", int level = 0);

    void runOnFunction(IRFunction &F) override;
};

#endif //COMPILER_REGISTERPASS_H

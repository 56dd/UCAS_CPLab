#ifndef COMPILER_CUTDEADCODEPASS_H
#define COMPILER_CUTDEADCODEPASS_H

#include "Pass.h"

class CutDeadCodePass : public FunctionPass {
public:
    explicit CutDeadCodePass(std::string name, int level = 1);

    void runOnFunction(IRFunction &F) override;
};


#endif //COMPILER_CUTDEADCODEPASS_H

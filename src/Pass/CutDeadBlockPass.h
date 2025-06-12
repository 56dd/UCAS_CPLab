#ifndef COMPILER_CUTDEADBLOCKPASS_H
#define COMPILER_CUTDEADBLOCKPASS_H

#include "Pass.h"

class CutDeadBlockPass : public FunctionPass {
private:
    enum dType {
        NONE,
        NO_CODE,
        NO_BRANCH
    };
public:
    explicit CutDeadBlockPass(std::string name = "", int level = 2);

    void runOnFunction(IRFunction &F) override;
};


#endif //COMPILER_CUTDEADBLOCKPASS_H

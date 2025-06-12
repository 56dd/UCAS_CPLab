#ifndef COMPILER_RENAMEPASS_H
#define COMPILER_RENAMEPASS_H

#include "Pass.h"

class RenamePass : public FunctionPass {
public:
    explicit RenamePass(std::string name = "", int level = 0);

    void runOnFunction(IRFunction &F) override;
};


#endif //COMPILER_RENAMEPASS_H

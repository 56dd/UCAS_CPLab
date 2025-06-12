#ifndef COMPILER_GLOBALSUBEXPPASS_H
#define COMPILER_GLOBALSUBEXPPASS_H

#include "Pass.h"

class GlobalSubExpPass : public FunctionPass {
public:
    explicit GlobalSubExpPass(std::string name = "", int level = 1);

    void runOnFunction(IRFunction &F) override;
};


#endif //COMPILER_RENAMEPASS_H

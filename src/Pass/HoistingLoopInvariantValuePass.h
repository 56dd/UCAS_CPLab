#ifndef COMPILER_HOISTINGLOOPINVARIANTVALUEPASS_H
#define COMPILER_HOISTINGLOOPINVARIANTVALUEPASS_H

#include "Pass.h"
#include "utils/LoopInfo.h"
#include "IR/iMemory.h"

class HoistingLoopInvariantValuePass : public FunctionPass {
public:
    explicit HoistingLoopInvariantValuePass(std::string name = "", int level = 2);

    void runOnFunction(IRFunction &F) override;

private:
    static std::vector<IRValue *> findInvariantValue(LoopInfo *loop, ControlFlowGraph *cfg);

    static bool binaryOperandCondition(IRValue *op, std::set<IRValue *> *Set, LoopInfo *loop);

    static bool loadInstCondition(IRLoadInst *inst, std::set<IRValue *> *Set, LoopInfo *loop);

    static bool storeInstCondition(IRStoreInst *inst, std::set<IRValue *> *Set, LoopInfo *loop,
                                   ControlFlowGraph *cfg);
};


#endif //COMPILER_HOISTINGLOOPINVARIANTVALUEPASS_H

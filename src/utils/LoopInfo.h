#ifndef COMPILER_LOOPINFO_H
#define COMPILER_LOOPINFO_H


#include <vector>
#include "ControlFlowGraph.h"

class IRFunction;

class IRBasicBlock;

class IRValue;

class LoopInfo {
private:
    IRBasicBlock *preHeader{};
    IRBasicBlock *header{};
    IRBasicBlock *latch{};
    IRBasicBlock *exit{};
    std::vector<IRBasicBlock *> exiting;
    std::vector<IRBasicBlock *> basicBlockList;

    static bool internelIsFullyExitingBlock(IRBasicBlock *&BB, IRBasicBlock *exit);

public:

    LoopInfo();

    LoopInfo(IRBasicBlock *preHeader, IRBasicBlock *header, IRBasicBlock *latch, IRBasicBlock *exit,
             std::vector<IRBasicBlock *> BBList);

    IRBasicBlock *getPreHeader() const;

    IRBasicBlock *getHeader() const;

    IRBasicBlock *getLatch() const;

    const std::vector<IRBasicBlock *> &getExiting() const;

    IRBasicBlock *getExit() const;

    static std::vector<LoopInfo *> findLoop(IRFunction *F, ControlFlowGraph *cfg);

    const std::vector<IRBasicBlock *> &getBasicBlockList() const;

    static bool isLoopInvariant(IRValue *value, LoopInfo *loop);

    static unsigned belongedToLoopNums(IRBasicBlock *BB);
};


#endif //COMPILER_LOOPINFO_H

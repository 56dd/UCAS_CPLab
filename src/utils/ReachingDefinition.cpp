#include "ReachingDefinition.h"
#include "IR/IRInstruction.h"
#include "IR/iMemory.h"
#include "IR/IRGlobalVariable.h"
#include "utils/ControlFlowGraph.h"
#include "utils/ControlFlowGraphVertex.h"

std::map<ControlFlowGraphVertex *, bool> ReachingDefinition::visited;

std::set<IRStoreInst *> ReachingDefinition::getReachingDefinitions(IRGlobalVariable *GV, IRInstruction *inst) {
    std::set<IRStoreInst *> reachingDefinitions;
    auto instList = inst->getParent()->getInstList();
    for (auto Inst: instList) {
        if (Inst == inst)
            break;
        if (IRStoreInst::classof(Inst) &&
            dynamic_cast<IRStoreInst *>(Inst)->getPointerOperand() == dynamic_cast<IRValue *>(GV)) {
            reachingDefinitions.clear();
            reachingDefinitions.insert(dynamic_cast<IRStoreInst *>(Inst));
        }
    }
    if (reachingDefinitions.empty()) {
        ControlFlowGraph cfg(inst->getParent()->getParent());
        visited.clear();
        for (auto node: cfg.getVertexFromBasicBlock(inst->getParent())->getPredecessors()) {
            if (visited[node])
                continue;
            visited[node] = true;
            bruteForce(GV, node, &reachingDefinitions);
        }
    }
    return reachingDefinitions;
}

void ReachingDefinition::bruteForce(IRGlobalVariable *GV, ControlFlowGraphVertex *node, std::set<IRStoreInst *> *Set) {
    auto instList = node->getBasicBlock()->getInstList();
    for (auto rit = instList.rbegin(); rit != instList.rend(); ++rit) {
        auto inst = *rit;
        if (IRStoreInst::classof(inst) &&
            dynamic_cast<IRStoreInst *>(inst)->getPointerOperand() == dynamic_cast<IRValue *>(GV)) {
            Set->insert(dynamic_cast<IRStoreInst *>(inst));
            return;
        }
    }
    for (auto pre: node->getPredecessors()) {
        if (visited[pre])
            continue;
        visited[pre] = true;
        bruteForce(GV, pre, Set);
    }
}

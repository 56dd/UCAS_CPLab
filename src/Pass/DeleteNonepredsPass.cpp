#include "DeleteNonepredsPass.h"
#include "IR/IRValue.h"
#include "IR/InstrTypes.h"
#include "IR/iPHINdoe.h"
#include "utils/ControlFlowGraph.h"
#include "utils/ControlFlowGraphVertex.h"
#include <algorithm>

DeleteNonePredsPass::DeleteNonePredsPass(std::string name, int level) : FunctionPass(std::move(name), level) {

}

void DeleteNonePredsPass::runOnFunction(IRFunction &F) {
    auto &BBList = F.getBasicBlockList();
    ControlFlowGraph cfg(&F);
    std::map<IRBasicBlock *, bool> visited;
    dfs(F.getEntryBlock(), &cfg, visited);
    std::vector<IRBasicBlock *> bin;
    for (auto BB : BBList) {
        if (!visited[BB]) {
            bin.push_back(BB);
        }
    }
    for (auto BB : bin) {
        for (auto inst : BB->getInstList())
            inst->dropAllReferences();
        BB->getInstList().clear();
        BBList.erase(std::find(BBList.begin(), BBList.end(), BB));
    }
}

void DeleteNonePredsPass::dfs(IRBasicBlock *block, ControlFlowGraph *G, std::map<IRBasicBlock *, bool> &visited) {
    visited[block] = true;
    for (auto node : G->getVertexFromBasicBlock(block)->getSuccessors()) {
        if (!visited[node->getBasicBlock()]) {
            dfs(node->getBasicBlock(), G, visited);
        }
    }
}

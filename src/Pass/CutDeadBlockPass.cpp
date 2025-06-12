#include "CutDeadBlockPass.h"
#include "IR/iTerminators.h"
#include "IR/iPHINdoe.h"

#include <utility>

void CutDeadBlockPass::runOnFunction(IRFunction &F) {
    bool codeChanged = true;
    auto &BBList = F.getBasicBlockList();
    while (codeChanged) {
        codeChanged = false;
        IRBasicBlock *deadBlock = nullptr;
        dType dTy;
        dTy = NONE;
        for (auto BB: BBList) {
            if (BB == F.getEntryBlock())
                continue;
            auto instList = BB->getInstList();
            auto successor = BB->findSuccessor();
            auto predecessor = BB->findPredecessor();
            if (instList.size() == 1 && successor.size() == 1) {
                auto succPred = successor[0]->findPredecessor();
                bool flag = true;
                for (auto pre: predecessor) {
                    if (std::find(succPred.begin(), succPred.end(), pre) != succPred.end()) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    deadBlock = BB;
                    break;
                }
            }
        }
        if (deadBlock) {
            codeChanged = true;
            auto predecessor = deadBlock->findPredecessor();
            auto successor = deadBlock->findSuccessor();
            auto &instList = deadBlock->getInstList();
            for (auto use: deadBlock->getUses()) {
                auto inst = dynamic_cast<IRInstruction *>(use->getUser());
                if (IRBranchInst::classof(inst)) {
                    use->set(dynamic_cast<IRValue *>(successor[0]));
                } else if (IRPHINode::classof(inst)) {
                    use->set(dynamic_cast<IRValue *>(predecessor[0]));
                } else {
                    assert(0 && "wtf");
                }
            }
            instList[0]->dropAllReferences();
            instList.erase(std::find(instList.begin(), instList.end(), instList[0]));
            BBList.erase(std::find(BBList.begin(), BBList.end(), deadBlock));
        }
    }
}

CutDeadBlockPass::CutDeadBlockPass(std::string name, int level) : FunctionPass(std::move(name), level) {

}

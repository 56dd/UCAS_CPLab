#include "AggressiveDeadCodeEliminatePass.h"
#include "utils/ControlDependenceGraph.h"
#include "utils/ControlDependenceGraphVertex.h"
#include "IR/IRInstruction.h"
#include "IR/iTerminators.h"
#include "IR/iPHINdoe.h"
#include <queue>
#include <set>

AggressiveDeadCodeEliminatePass::AggressiveDeadCodeEliminatePass(std::string name, int level) : FunctionPass(name,
                                                                                                             level) {

}

void AggressiveDeadCodeEliminatePass::runOnFunction(IRFunction &F) {
    ControlDependenceGraph cdg(&F);
    std::queue<IRInstruction *> workList;
    std::set<IRInstruction *> activeInstSet;
    std::set<IRBasicBlock *> activeBlockSet;

    initWorkList(&F, &workList, &activeInstSet, &activeBlockSet);

    while (!workList.empty()) {
        auto activeInst = workList.front();
        workList.pop();
        // 将对活跃变量使用的 Operand 定值的的指令加入活跃指令集合
        auto phi = dynamic_cast<IRPHINode *>(activeInst);
        if (phi) {
            for (unsigned i = 0, E = phi->getNumIncomingValues(); i < E; ++i) {
                auto BB = phi->getIncomingBlock(i);
                if (std::find(F.getBasicBlockList().begin(), F.getBasicBlockList().end(), BB) ==
                    F.getBasicBlockList().end())
                    continue;
                auto inst = dynamic_cast<IRInstruction *>(phi->getIncomingBlock(i)->getTerminator());
                activeBlockSet.insert(phi->getIncomingBlock(i));
                if (activeInstSet.find(inst) == activeInstSet.end()) {
                    activeInstSet.insert(inst);
                    workList.push(inst);
                }
            }
        }
        auto br = dynamic_cast<IRBranchInst *>(activeInst);
        if (br) {
            for (unsigned i = 0, E = br->getNumSuccessors(); i < E; ++i) {
                auto BB = br->getSuccessor(i);
                activeBlockSet.insert(BB);
                auto inst = dynamic_cast<IRInstruction *>(BB->getTerminator());
                if (activeInstSet.find(inst) == activeInstSet.end()) {
                    activeInstSet.insert(inst);
                    workList.push(inst);
                }
            }
        }
        if (phi) {
            for (unsigned i = 0, E = phi->getNumIncomingValues(); i < E; ++i) {
                auto BB = phi->getIncomingBlock(i);
                if (std::find(F.getBasicBlockList().begin(), F.getBasicBlockList().end(), BB) ==
                    F.getBasicBlockList().end())
                    continue;
                auto inst = dynamic_cast<IRInstruction *>(phi->getIncomingValue(i));
                if (inst == nullptr)
                    continue;
                if (activeInstSet.find(inst) == activeInstSet.end()) {
                    activeBlockSet.insert(inst->getParent());
                    activeInstSet.insert(inst);
                    workList.push(inst);
                }
            }
        } else {
            for (unsigned i = 0, E = activeInst->getNumOperands(); i < E; ++i) {
                auto inst = dynamic_cast<IRInstruction *>(activeInst->getOperand(i));
                if (inst == nullptr)
                    continue;
                if (activeInstSet.find(inst) == activeInstSet.end()) {
                    activeBlockSet.insert(inst->getParent());
                    activeInstSet.insert(inst);
                    workList.push(inst);
                }
            }
        }
        // 将活跃指令控制依赖的分支语句加入活跃指令集合
        auto vertex = cdg.getVertexFromBasicBlock(activeInst->getParent());
        for (auto pred: vertex->getPredecessors()) {
            auto predBB = pred->getBasicBlock();
            if (predBB == nullptr)
                continue;
            auto inst = dynamic_cast<IRInstruction *>(predBB->getTerminator());
            if (activeInstSet.find(inst) == activeInstSet.end()) {
                activeBlockSet.insert(inst->getParent());
                activeInstSet.insert(inst);
                workList.push(inst);
            }
        }
    }

    std::vector<IRInstruction *> bin;
    for (auto BB: F.getBasicBlockList()) {
        for (auto inst: BB->getInstList()) {
            if (activeInstSet.find(inst) == activeInstSet.end()) {
                bin.push_back(inst);
            }
        }
    }

    for (auto trash: bin) {
        auto &instList = trash->getParent()->getInstList();
        trash->dropAllReferences();
        instList.erase(std::find(instList.begin(), instList.end(), trash));
    }

    std::vector<IRBasicBlock *> BBbin;
    for (auto BB: F.getBasicBlockList()) {
        if (activeBlockSet.find(BB) == activeBlockSet.end())
            BBbin.push_back(BB);
    }

    auto &BBList = F.getBasicBlockList();
    for (auto trash: BBbin) {
        BBList.erase(std::find(BBList.begin(), BBList.end(), trash));
    }

    auto rCfg = cdg.getRCfg();

    for (auto BB: activeBlockSet) {
        if (!BB->hasTerminator()) {
            auto DT = rCfg.getVertexFromBasicBlock(BB)->getDominatorTreeNode();
            IRBasicBlock *dest = nullptr;
            for (DT = DT->idom; DT->basicBlock; DT = DT->idom) {
                if (activeBlockSet.find(DT->basicBlock) != activeBlockSet.end()) {
                    dest = DT->basicBlock;
                    break;
                }
            }
            assert(dest && "wtf?");
            new IRBranchInst(dest, nullptr, nullptr, BB);
        }
    }
}

void AggressiveDeadCodeEliminatePass::initWorkList(IRFunction *F, std::queue<IRInstruction *> *Queue,
                                                   std::set<IRInstruction *> *activeInstSet,
                                                   std::set<IRBasicBlock *> *activeBlockSet) {
    activeBlockSet->insert(F->getEntryBlock());
    activeInstSet->insert(F->getEntryBlock()->getTerminator());
    Queue->push(F->getEntryBlock()->getTerminator());
    for (auto BB: F->getBasicBlockList()) {
        for (auto inst: BB->getInstList()) {
            if (isNaturalActiveInst(inst)) {
                activeBlockSet->insert(inst->getParent());
                activeInstSet->insert(inst);
                Queue->push(inst);
            }
        }
    }
}

bool AggressiveDeadCodeEliminatePass::isNaturalActiveInst(IRInstruction *inst) {
    switch (inst->getOpcode()) {
        case IRInstruction::Call:
        case IRInstruction::Store:
        case IRInstruction::Ret:
        case IRInstruction::Memcpy:
            return true;
    }
    return false;
}

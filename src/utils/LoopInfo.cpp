#include "LoopInfo.h"

#include <utility>
#include "IR/iOther.h"
#include "IR/IRConstant.h"
#include "IR/IRArgument.h"
#include "utils/ControlFlowGraph.h"
#include "ControlFlowGraph.h"

std::vector<LoopInfo *> LoopInfo::findLoop(IRFunction *F, ControlFlowGraph *cfg) {
    std::vector<LoopInfo *> loopList;
    auto BBList = F->getBasicBlockList();
    for (auto BB: BBList) {
        auto terminator = BB->getTerminator();
        if (terminator->getNumSuccessors() == 2) {
            IRBasicBlock *successor0 = terminator->getSuccessor(0);
            IRBasicBlock *successor1 = terminator->getSuccessor(1);
            if (DominatorTree::isAncestor(successor1->getDominatorTree(cfg), BB->getDominatorTree(cfg))) {
                std::swap(successor0, successor1);
            }
            if (DominatorTree::isAncestor(successor0->getDominatorTree(cfg), BB->getDominatorTree(cfg))) {
                auto header = successor0;
                auto preHeader = dynamic_cast<IRInstruction *>(header->getUses()[0]->getUser())->getParent();
                auto exiting = BB;
                auto exit = successor1;
                std::vector<IRBasicBlock *> loopBBList;
                loopBBList.clear();
                for (auto ptr = std::find(BBList.begin(), BBList.end(), header),
                             ePtr = std::find(BBList.begin(), BBList.end(), exit); ptr != ePtr; ++ptr) {
                    if (internelIsFullyExitingBlock(*ptr, exit)) {
                        continue;
                    }
                    loopBBList.push_back(*ptr);
                }
                loopList.push_back(new LoopInfo(preHeader, header, exiting, exit, loopBBList));
            }
        } else {
            continue;
        }
    }
    return loopList;
}

LoopInfo::LoopInfo(IRBasicBlock *preHeader, IRBasicBlock *header, IRBasicBlock *latch, IRBasicBlock *exit,
                   std::vector<IRBasicBlock *> BBList) :
        preHeader(preHeader), header(header), latch(latch), exit(exit), basicBlockList(std::move(BBList)) {
    for (auto BB: basicBlockList) {
        auto terminator = BB->getTerminator();
        for (unsigned i = 0, E = terminator->getNumSuccessors(); i < E; ++i) {
            auto successor = terminator->getSuccessor(i);
            if (std::find(basicBlockList.begin(), basicBlockList.end(), successor) == basicBlockList.end()) {
                exiting.push_back(BB);
                break;
            }
        }
    }
}

IRBasicBlock *LoopInfo::getPreHeader() const {
    return preHeader;
}

IRBasicBlock *LoopInfo::getHeader() const {
    return header;
}

IRBasicBlock *LoopInfo::getExit() const {
    return exit;
}

const std::vector<IRBasicBlock *> &LoopInfo::getBasicBlockList() const {
    return basicBlockList;
}

IRBasicBlock *LoopInfo::getLatch() const {
    return latch;
}

const std::vector<IRBasicBlock *> &LoopInfo::getExiting() const {
    return exiting;
}

bool LoopInfo::internelIsFullyExitingBlock(IRBasicBlock *&BB, IRBasicBlock *exit) {
    auto terminator = BB->getTerminator();
    for (unsigned i = 0, E = terminator->getNumSuccessors(); i < E; ++i) {
        auto successor = terminator->getSuccessor(i);
        if (successor != exit) {
            return false;
        }
    }
    return true;
}

bool LoopInfo::isLoopInvariant(IRValue *value, LoopInfo *loop) {
auto loopBBList = loop->getBasicBlockList();
    if (IRConstant::classof(value) || IRArgument::classof(value)) {
        return true;
    }
    auto inst = dynamic_cast<IRInstruction *>(value);
    if (std::find(loopBBList.begin(), loopBBList.end(), inst->getParent()) == loopBBList.end()) {
        return true;
    }
    return false;
}

unsigned LoopInfo::belongedToLoopNums(IRBasicBlock *BB) {
    unsigned count = 0;
    auto F = BB->getParent();
    ControlFlowGraph cfg(F);
    DominatorTree::getDominatorTree(&cfg);
    auto loopList = findLoop(F, &cfg);
    for (auto loop : loopList) {
        auto BBList = loop->getBasicBlockList();
        if (std::find(BBList.begin(), BBList.end(), BB) != BBList.end()) {
            count++;
        }
    }
    return count;
}

LoopInfo::LoopInfo() = default;

#include "HoistingLoopInvariantValuePass.h"
#include "utils/ControlFlowGraph.h"
#include "utils/ControlFlowGraphVertex.h"
#include "utils/ReachingDefinition.h"
#include "IR/iOperators.h"

#include <utility>

HoistingLoopInvariantValuePass::HoistingLoopInvariantValuePass(std::string name, int level) : FunctionPass(
        std::move(name), level) {

}

void HoistingLoopInvariantValuePass::runOnFunction(IRFunction &F) {
    ControlFlowGraph cfg(&F);
    DominatorTree::getDominatorTree(&cfg);
    auto LoopList = LoopInfo::findLoop(&F, &cfg);
    for (auto loop: LoopList) {
        auto invariantValueList = findInvariantValue(loop, &cfg);
        auto preHeader = loop->getPreHeader();
        auto &preHeaderBB = loop->getPreHeader()->getInstList();
        for (auto iV: invariantValueList) {
            auto iVInst = dynamic_cast<IRInstruction *>(iV);
            auto iVBB = iVInst->getParent();
            auto &iVBBInstList = iVBB->getInstList();
            iVBBInstList.erase(std::find(iVBBInstList.begin(), iVBBInstList.end(), iVInst));
            iVInst->setParent(preHeader);
            preHeaderBB.emplace(preHeaderBB.end() - 1, iVInst);
        }
    }
}

std::vector<IRValue *> HoistingLoopInvariantValuePass::findInvariantValue(LoopInfo *loop, ControlFlowGraph *cfg) {
    std::vector<IRValue *> invariantValueList;
    std::set<IRValue *> invariantValueSet;
    auto BBList = loop->getBasicBlockList();
    unsigned size = 0;
    do {
        size = invariantValueSet.size();
        for (auto BB: BBList) {
            auto &instList = BB->getInstList();
            for (auto inst: instList) {
                if (invariantValueSet.find(dynamic_cast<IRValue *>(inst)) != invariantValueSet.end()) {
                    continue;
                }
                if (inst->isBinaryOp()) {
                    if (IRSetCondInst::classof(inst))
                        continue;
                    auto op0 = inst->getOperand(0);
                    auto op1 = inst->getOperand(1);
                    if (binaryOperandCondition(op0, &invariantValueSet, loop) &&
                        binaryOperandCondition(op1, &invariantValueSet, loop)) {
                        invariantValueSet.insert(dynamic_cast<IRValue *>(inst));
                    }
                } else if (IRLoadInst::classof(inst)) {
                    if (loadInstCondition(dynamic_cast<IRLoadInst *>(inst), &invariantValueSet, loop)) {
                        invariantValueSet.insert(dynamic_cast<IRValue *>(inst));
                    }
                } else if (IRStoreInst::classof(inst)) {
                    if (storeInstCondition(dynamic_cast<IRStoreInst *>(inst), &invariantValueSet, loop, cfg)) {
                        invariantValueSet.insert(dynamic_cast<IRValue *>(inst));
                    }
                }
            }
        }
    } while (size < invariantValueSet.size());
    for (auto BB: BBList) {
        auto &instList = BB->getInstList();
        for (auto inst: instList) {
            if (invariantValueSet.find(dynamic_cast<IRValue *>(inst)) != invariantValueSet.end()) {
                invariantValueList.push_back(dynamic_cast<IRValue *>(inst));
            }
        }
    }
    return invariantValueList;
}

bool HoistingLoopInvariantValuePass::binaryOperandCondition(IRValue *op, std::set<IRValue *> *Set, LoopInfo *loop) {
    if (op->getValueType() == IRValue::ConstantVal)  // 是常数
        return true;

    if (Set->find(op) != Set->end()) { // 是循环不变量
        return true;
    }

    auto BBList = loop->getBasicBlockList();
    if (dynamic_cast<IRArgument *>(op) ||
        std::find(BBList.begin(), BBList.end(), dynamic_cast<IRInstruction *>(op)->getParent()) ==
        BBList.end()) { // 定值在循环外
        return true;
    }

    return false;
}

bool HoistingLoopInvariantValuePass::loadInstCondition(IRLoadInst *inst, std::set<IRValue *> *Set, LoopInfo *loop) {
    /*!
     * 经过 mem2reg 后 load 只会有两种情况：
     * 1. 全局变量：
     * 2. 数组地址
     */

    auto ptr = inst->getPointerOperand();
    if (IRGlobalVariable::classof(ptr)) {
        /*!
         * 全局变量的条件：
         * 1. 在循环中没有到达定值：提到 preheader 提前 load
         * 2. 只有一个到达定值，且该定值为循环不变量：用该定值代替 load 的值，此时要返回 false
         * 由于经过了 mem2reg，且 code_gen 中没有一个 sample 有非数组的全局变量。这意味着对于全局变量的指针，没有 store。
         * 所以只需要考虑第一种情况（注意：此条件仅针对 prj3 中的样例成立，是对特定程序的激进优化）
         */

        auto reachingDefinitions = ReachingDefinition::getReachingDefinitions(dynamic_cast<IRGlobalVariable *>(ptr),
                                                                              inst);
        // 1. 循环中没有到达定值
        auto loopBBList = loop->getBasicBlockList();
        bool hasDefinitionInLoop = false;
        for (auto stInst: reachingDefinitions) {
            if (std::find(loopBBList.begin(), loopBBList.end(), stInst->getParent()) != loopBBList.end()) {
                hasDefinitionInLoop = true;
                break;
            }
        }
        if (!hasDefinitionInLoop) {
            return true;
        }
        // 2. 只有一个到达定值，且该定值为循环不变量
        if (reachingDefinitions.size() == 1) {
            auto definition = *reachingDefinitions.begin();
            if (std::find(loopBBList.begin(), loopBBList.end(), definition->getParent()) == loopBBList.end()
                || Set->find(definition->getOperand(0)) != Set->end()) {
                inst->replaceAllUsesWith(definition->getOperand(0));
            }
        }
    } else {
        /*!
         * 数组地址的条件：
         * 1. 数组地址是循环不变量（注意：此条件仅针对 prj3 中的性能样例成立（?），是对特定程序的激进优化）
         */
//        if (Set->find(ptr) != Set->end()) {
//            return true;
//        }
    }

    return false;
}

bool HoistingLoopInvariantValuePass::storeInstCondition(IRStoreInst *inst, std::set<IRValue *> *Set, LoopInfo *loop,
                                                        ControlFlowGraph *cfg) {
    /*!
     * 经过 mem2reg 后 store 只会有两种情况：
     * 1. 全局变量
     * 2. 数组地址
     */

    /*!
     * store 的条件：
     * 1. 值和指针都是循环不变量
     * 2. store 所在块是所有 exiting 块的必经节点块
     */

    if (Set->find(inst->getOperand(0)) == Set->end()) {
        return false;
    }

    if (Set->find(inst->getOperand(1)) == Set->end()) {
        return false;
    }

    auto exiting = loop->getExiting();
    for (auto exitingBB: exiting) {
        if (!DominatorTree::isAncestor(inst->getParent()->getDominatorTree(cfg), exitingBB->getDominatorTree(cfg))) {
            return false;
        }
    }
    return true;
}
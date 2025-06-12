#include "StrengthReductionPass.h"

#include <utility>
#include "utils/LoopInfo.h"
#include "IR/iPHINdoe.h"
#include "IR/iOperators.h"
#include "IR/IRConstant.h"
#include "Pass/ConstantPass.h"
#include "Pass/GlobalSubExpPass.h"
#include "Pass/LocalSubExpPass.h"
#include "Pass/EliminateBasicInductionVarPass.h"
#include <iostream>

StrengthReductionPass::StrengthReductionPass(std::string name, int level) : FunctionPass(std::move(name), level) {

}

void StrengthReductionPass::runOnFunction(IRFunction &F) {
    ControlFlowGraph cfg(&F);
    DominatorTree::getDominatorTree(&cfg);
    bool codeIsChanged = true;
    ConstantPass CP("ConstantPass");
    LocalSubExpPass LSEP("LocalSubExpPass");
    GlobalSubExpPass GSEP("GlobalSubExpPass");
    EliminateBasicInductionVarPass EBIVP("EliminateBasicInductionVarPass");
    while (codeIsChanged) {
        codeIsChanged = false;
        LSEP.runOnFunction(F);
        GSEP.runOnFunction(F);
        CP.runOnFunction(F);
        EBIVP.runOnFunction(F);
        auto loopList = LoopInfo::findLoop(&F, &cfg);
        for (auto loop: loopList) {
            auto loopBBList = loop->getBasicBlockList();
            auto BISet = BasicInductionVariable::findBasicInductionVar(loop);
            while (!BISet.empty()) {
                auto ptrBI = BISet.begin();
                auto BI = *ptrBI;
                BISet.erase(ptrBI);
                codeIsChanged |= reduction(&F, BI, loop, &BISet);
            }
        }
    }
}

bool StrengthReductionPass::reduction(IRFunction *F, BasicInductionVariable *const &BI, LoopInfo *loop,
                                      std::set<BasicInductionVariable *> *BISet) {
    bool codeIsChanged = false;
    IRBinaryOperator *IV = nullptr;
    auto &preheaderInstList = loop->getPreHeader()->getInstList();
    auto &BICalcInstList = BI->getCalcNode()->getParent()->getInstList();
    // 第一类归纳变量，使用的是基本归纳变量的phiNode
    while (IV = findInductionVarUsePhi(BI, loop)) {
        codeIsChanged = true;
        auto &IVinstList = IV->getParent()->getInstList();
        IRValue *loopInvariant = nullptr;
        if (IV->getOperand(0) == dynamic_cast<IRValue *>(BI->getPhiNode())) {
            loopInvariant = IV->getOperand(1);
        } else {
            loopInvariant = IV->getOperand(0);
        }
        IRBinaryOperator *newBaseVal = nullptr, *newBI = nullptr, *newIncrementVal = nullptr;
        IRPHINode *newPhi = nullptr;
        switch (IV->getOpcode()) {
            case IRInstruction::Sub:
                // 在 preheader 中插入初始值的计算
                newBaseVal = IRBinaryOperator::create(IRInstruction::Sub, BI->getBaseVal(), loopInvariant,
                                                      std::to_string(F->getCount()));
                F->addCount();
                newBaseVal->setParent(loop->getPreHeader());
                preheaderInstList.insert(preheaderInstList.end() - 1, newBaseVal);
                // 在 header 中插入 phi
                newPhi = new IRPHINode(newBaseVal->getType(), nullptr, std::to_string(F->getCount()));
                F->addCount();
                newPhi->setParent(loop->getHeader());
                loop->getHeader()->addInstructionToFront(dynamic_cast<IRInstruction *>(newPhi));

                // 在 BI->getCalcNode 下方插入新的 BI
                newBI = IRBinaryOperator::create(IRInstruction::Add, dynamic_cast<IRValue *>(newPhi),
                                                 BI->getIncrementVal(), std::to_string(F->getCount()));
                F->addCount();
                newBI->setParent(BI->getCalcNode()->getParent());
                BICalcInstList.insert(
                        std::find(BICalcInstList.begin(), BICalcInstList.end(),
                                  dynamic_cast<IRInstruction *>(BI->getCalcNode())) + 1,
                        dynamic_cast<IRInstruction *>(newBI));
                // 将 IV 替换成 newPhi
                IV->replaceAllUsesWith(dynamic_cast<IRValue *>(newPhi));
                IV->dropAllReferences();
                IVinstList.erase(std::find(IVinstList.begin(), IVinstList.end(), dynamic_cast<IRInstruction *>(IV)));
                // 填入 newPhi 的参数
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBaseVal), loop->getPreHeader());
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBI), loop->getLatch());
                break;
            case IRInstruction::Add:
                // 在 preheader 中插入初始值的计算
                newBaseVal = IRBinaryOperator::create(IRInstruction::Add, loopInvariant, BI->getBaseVal(),
                                                      std::to_string(F->getCount()));
                F->addCount();
                newBaseVal->setParent(loop->getPreHeader());
                preheaderInstList.insert(preheaderInstList.end() - 1, newBaseVal);
                // 在 header 中插入 phi
                newPhi = new IRPHINode(newBaseVal->getType(), nullptr, std::to_string(F->getCount()));
                F->addCount();
                newPhi->setParent(loop->getHeader());
                loop->getHeader()->addInstructionToFront(dynamic_cast<IRInstruction *>(newPhi));

                // 在 BI->getCalcNode 下方插入新的 BI
                newBI = IRBinaryOperator::create(IRInstruction::Add, dynamic_cast<IRValue *>(newPhi),
                                                 BI->getIncrementVal(), std::to_string(F->getCount()));
                F->addCount();
                newBI->setParent(BI->getCalcNode()->getParent());
                BICalcInstList.insert(
                        std::find(BICalcInstList.begin(), BICalcInstList.end(),
                                  dynamic_cast<IRInstruction *>(BI->getCalcNode())) + 1,
                        dynamic_cast<IRInstruction *>(newBI));
                // 将 IV 替换成 newPhi
                IV->replaceAllUsesWith(dynamic_cast<IRValue *>(newPhi));
                IV->dropAllReferences();
                IVinstList.erase(std::find(IVinstList.begin(), IVinstList.end(), dynamic_cast<IRInstruction *>(IV)));
                // 填入 newPhi 的参数
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBaseVal), loop->getPreHeader());
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBI), loop->getLatch());
                break;
            case IRInstruction::Mul:
                // 在 preheader 中插入初始值的计算
                newBaseVal = IRBinaryOperator::create(IRInstruction::Mul, loopInvariant, BI->getBaseVal(),
                                                      std::to_string(F->getCount()));
                F->addCount();
                newBaseVal->setParent(loop->getPreHeader());
                preheaderInstList.insert(preheaderInstList.end() - 1, newBaseVal);
                // 在 preheader 中插入增量的计算
                newIncrementVal = IRBinaryOperator::create(IRInstruction::Mul, loopInvariant, BI->getIncrementVal(),
                                                           std::to_string(F->getCount()));
                F->addCount();
                newIncrementVal->setParent(loop->getPreHeader());
                preheaderInstList.insert(preheaderInstList.end() - 1, newIncrementVal);
                // 在 header 中插入 phi
                newPhi = new IRPHINode(newBaseVal->getType(), nullptr, std::to_string(F->getCount()));
                F->addCount();
                newPhi->setParent(loop->getHeader());
                loop->getHeader()->addInstructionToFront(dynamic_cast<IRInstruction *>(newPhi));

                // 在 BI->getCalcNode 下方插入新的 BI
                newBI = IRBinaryOperator::create(IRInstruction::Add, dynamic_cast<IRValue *>(newPhi),
                                                 newIncrementVal, std::to_string(F->getCount()));
                F->addCount();
                newBI->setParent(BI->getCalcNode()->getParent());
                BICalcInstList.insert(
                        std::find(BICalcInstList.begin(), BICalcInstList.end(),
                                  dynamic_cast<IRInstruction *>(BI->getCalcNode())) + 1,
                        dynamic_cast<IRInstruction *>(newBI));
                // 将 IV 替换成 newPhi
                IV->replaceAllUsesWith(dynamic_cast<IRValue *>(newPhi));
                IV->dropAllReferences();
                IVinstList.erase(std::find(IVinstList.begin(), IVinstList.end(), dynamic_cast<IRInstruction *>(IV)));
                // 填入 newPhi 的参数
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBaseVal), loop->getPreHeader());
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBI), loop->getLatch());
                break;
            default:
                assert(0 && "wtf");
        }
        BISet->insert(new BasicInductionVariable(newPhi, newBI, loop));
    }
    // 第二类归纳变量，使用的是基本归纳变量的calcNode
    while (IV = findInductionVarUseCalc(BI, loop)) {
        codeIsChanged = true;
        auto &IVinstList = IV->getParent()->getInstList();
        IRValue *loopInvariant = nullptr;
        if (IV->getOperand(0) == dynamic_cast<IRValue *>(BI->getCalcNode())) {
            loopInvariant = IV->getOperand(1);
        } else {
            loopInvariant = IV->getOperand(0);
        }
        IRBinaryOperator *newBaseVal = nullptr, *newBI = nullptr, *newIncrementVal = nullptr;
        IRPHINode *newPhi = nullptr;
        switch (IV->getOpcode()) {
            case IRInstruction::Sub:
                // 在 preheader 中插入初始值的计算
                newBaseVal = IRBinaryOperator::create(IRInstruction::Sub, BI->getBaseVal(), loopInvariant,
                                                      std::to_string(F->getCount()));
                F->addCount();
                newBaseVal->setParent(loop->getPreHeader());
                preheaderInstList.insert(preheaderInstList.end() - 1, newBaseVal);
                // 在 header 中插入 phi
                newPhi = new IRPHINode(newBaseVal->getType(), nullptr, std::to_string(F->getCount()));
                F->addCount();
                newPhi->setParent(loop->getHeader());
                loop->getHeader()->addInstructionToFront(dynamic_cast<IRInstruction *>(newPhi));

                // 在 BI->getCalcNode 下方插入新的 BI
                newBI = IRBinaryOperator::create(IRInstruction::Add, dynamic_cast<IRValue *>(newPhi),
                                                 BI->getIncrementVal(), std::to_string(F->getCount()));
                F->addCount();
                newBI->setParent(BI->getCalcNode()->getParent());
                BICalcInstList.insert(
                        std::find(BICalcInstList.begin(), BICalcInstList.end(),
                                  dynamic_cast<IRInstruction *>(BI->getCalcNode())) + 1,
                        dynamic_cast<IRInstruction *>(newBI));
                // 将 IV 替换成 newBI
                IV->replaceAllUsesWith(dynamic_cast<IRValue *>(newBI));
                IV->dropAllReferences();
                IVinstList.erase(std::find(IVinstList.begin(), IVinstList.end(), dynamic_cast<IRInstruction *>(IV)));
                // 填入 newPhi 的参数
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBaseVal), loop->getPreHeader());
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBI), loop->getLatch());
                break;
            case IRInstruction::Add:
                // 在 preheader 中插入初始值的计算
                newBaseVal = IRBinaryOperator::create(IRInstruction::Add, loopInvariant, BI->getBaseVal(),
                                                      std::to_string(F->getCount()));
                F->addCount();
                newBaseVal->setParent(loop->getPreHeader());
                preheaderInstList.insert(preheaderInstList.end() - 1, newBaseVal);
                // 在 header 中插入 phi
                newPhi = new IRPHINode(newBaseVal->getType(), nullptr, std::to_string(F->getCount()));
                F->addCount();
                newPhi->setParent(loop->getHeader());
                loop->getHeader()->addInstructionToFront(dynamic_cast<IRInstruction *>(newPhi));

                // 在 BI->getCalcNode 下方插入新的 BI
                newBI = IRBinaryOperator::create(IRInstruction::Add, dynamic_cast<IRValue *>(newPhi),
                                                 BI->getIncrementVal(), std::to_string(F->getCount()));
                F->addCount();
                newBI->setParent(BI->getCalcNode()->getParent());
                BICalcInstList.insert(
                        std::find(BICalcInstList.begin(), BICalcInstList.end(),
                                  dynamic_cast<IRInstruction *>(BI->getCalcNode())) + 1,
                        dynamic_cast<IRInstruction *>(newBI));
                // 将 IV 替换成 newBI
                IV->replaceAllUsesWith(dynamic_cast<IRValue *>(newBI));
                IV->dropAllReferences();
                IVinstList.erase(std::find(IVinstList.begin(), IVinstList.end(), dynamic_cast<IRInstruction *>(IV)));
                // 填入 newPhi 的参数
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBaseVal), loop->getPreHeader());
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBI), loop->getLatch());
                break;
            case IRInstruction::Mul:
                // 在 preheader 中插入初始值的计算
                newBaseVal = IRBinaryOperator::create(IRInstruction::Mul, loopInvariant, BI->getBaseVal(),
                                                      std::to_string(F->getCount()));
                F->addCount();
                newBaseVal->setParent(loop->getPreHeader());
                preheaderInstList.insert(preheaderInstList.end() - 1, newBaseVal);
                // 在 preheader 中插入增量的计算
                newIncrementVal = IRBinaryOperator::create(IRInstruction::Mul, loopInvariant, BI->getIncrementVal(),
                                                           std::to_string(F->getCount()));
                F->addCount();
                newIncrementVal->setParent(loop->getPreHeader());
                preheaderInstList.insert(preheaderInstList.end() - 1, newIncrementVal);
                // 在 header 中插入 phi
                newPhi = new IRPHINode(newBaseVal->getType(), nullptr, std::to_string(F->getCount()));
                F->addCount();
                newPhi->setParent(loop->getHeader());
                loop->getHeader()->addInstructionToFront(dynamic_cast<IRInstruction *>(newPhi));

                // 在 BI->getCalcNode 下方插入新的 BI
                newBI = IRBinaryOperator::create(IRInstruction::Add, dynamic_cast<IRValue *>(newPhi),
                                                 newIncrementVal, std::to_string(F->getCount()));
                F->addCount();
                newBI->setParent(BI->getCalcNode()->getParent());
                BICalcInstList.insert(
                        std::find(BICalcInstList.begin(), BICalcInstList.end(),
                                  dynamic_cast<IRInstruction *>(BI->getCalcNode())) + 1,
                        dynamic_cast<IRInstruction *>(newBI));
                // 将 IV 替换成 newBI
                IV->replaceAllUsesWith(dynamic_cast<IRValue *>(newBI));
                IV->dropAllReferences();
                IVinstList.erase(std::find(IVinstList.begin(), IVinstList.end(), dynamic_cast<IRInstruction *>(IV)));
                // 填入 newPhi 的参数
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBaseVal), loop->getPreHeader());
                newPhi->addIncoming(dynamic_cast<IRValue *>(newBI), loop->getLatch());
                break;
            default:
                assert(0 && "wtf");
        }
        BISet->insert(new BasicInductionVariable(newPhi, newBI, loop));
    }
    return codeIsChanged;
}

IRBinaryOperator *StrengthReductionPass::findInductionVarUsePhi(BasicInductionVariable *const &BI, LoopInfo *loop) {
    auto loopBBList = loop->getBasicBlockList();
    for (auto BB: loopBBList) {
        auto instList = BB->getInstList();
        for (auto inst: instList) {
            if (inst == dynamic_cast<IRInstruction *>(BI->getCalcNode()))
                continue;
            if (inst->getOpcode() != IRInstruction::Add && inst->getOpcode() != IRInstruction::Mul &&
                inst->getOpcode() != IRInstruction::Sub)
                continue;
            auto BO = dynamic_cast<IRBinaryOperator *>(inst);
            if (BO->getOperand(0) == dynamic_cast<IRValue *>(BI->getPhiNode()) &&
                LoopInfo::isLoopInvariant(BO->getOperand(1), loop)
                ||
                BO->getOperand(1) == dynamic_cast<IRValue *>(BI->getPhiNode()) &&
                LoopInfo::isLoopInvariant(BO->getOperand(0), loop) && inst->getOpcode() != IRInstruction::Sub) {
                return BO;
            }
        }
    }
    return nullptr;
}

IRBinaryOperator *StrengthReductionPass::findInductionVarUseCalc(BasicInductionVariable *const &BI, LoopInfo *loop) {
    auto loopBBList = loop->getBasicBlockList();
    for (auto BB: loopBBList) {
        auto instList = BB->getInstList();
        for (auto inst: instList) {
            if (inst->getOpcode() != IRInstruction::Add && inst->getOpcode() != IRInstruction::Mul &&
                inst->getOpcode() != IRInstruction::Sub)
                continue;
            auto BO = dynamic_cast<IRBinaryOperator *>(inst);
            if (BO->getOperand(0) == dynamic_cast<IRValue *>(BI->getCalcNode()) &&
                LoopInfo::isLoopInvariant(BO->getOperand(1), loop)
                ||
                BO->getOperand(1) == dynamic_cast<IRValue *>(BI->getCalcNode()) &&
                LoopInfo::isLoopInvariant(BO->getOperand(0), loop) && inst->getOpcode() != IRInstruction::Sub) {
                return BO;
            }
        }
    }
    return nullptr;
}

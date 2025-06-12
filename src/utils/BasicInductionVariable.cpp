#include "BasicInductionVariable.h"

#include "IR/iOperators.h"
#include "IR/iPHINdoe.h"
#include "utils/LoopInfo.h"

BasicInductionVariable::BasicInductionVariable(IRPHINode *phi, IRBinaryOperator *BO, LoopInfo *loopInfo)
        : phiNode(phi), calcNode(BO), belongsTo(loopInfo) {
    if (BO->getOperand(0) == dynamic_cast<IRValue *>(phi))
        incrementVal = calcNode->getOperand(1);
    else
        incrementVal = calcNode->getOperand(0);
    for (unsigned i = 0, E = phi->getNumIncomingValues(); i < E; ++i) {
        if (phi->getIncomingValue(i) == dynamic_cast<IRValue *>(BO))
            continue;
        else {
            baseVal = phi->getIncomingValue(i);
            break;
        }
    }
}

IRValue *BasicInductionVariable::getIncrementVal() const {
    return incrementVal;
}

IRPHINode *BasicInductionVariable::getPhiNode() const {
    return phiNode;
}

IRBinaryOperator *BasicInductionVariable::getCalcNode() const {
    return calcNode;
}

LoopInfo *BasicInductionVariable::getBelongsTo() const {
    return belongsTo;
}

IRValue *BasicInductionVariable::getBaseVal() const {
    return baseVal;
}

std::set<BasicInductionVariable *> BasicInductionVariable::findBasicInductionVar(LoopInfo *loop) {
    std::set<BasicInductionVariable *> BISet;
    auto loopBBList = loop->getBasicBlockList();
    auto header = loop->getHeader();
    for (auto inst: header->getInstList()) {
        if (IRPHINode::classof(inst)) {
            auto phi = dynamic_cast<IRPHINode *>(inst);
            for (unsigned i = 0, E = phi->getNumIncomingValues(); i < E; ++i) {
                auto val = phi->getIncomingValue(i);
                auto BB = phi->getIncomingBlock(i);

                if (std::find(loopBBList.begin(), loopBBList.end(), BB) == loopBBList.end()) // 上一个块得是循环内的块
                    continue;

                auto BO = dynamic_cast<IRBinaryOperator *>(val);

                if (BO == nullptr) // 值必须是指令
                    continue;

                if (BO->getOpcode() != IRInstruction::Add) // 是加法
                    continue;

                if (std::find(loopBBList.begin(), loopBBList.end(), BO->getParent()) == loopBBList.end()) // 加法在循环内
                    continue;

                if (BO->getOperand(0) == dynamic_cast<IRValue *>(phi) && LoopInfo::isLoopInvariant(BO->getOperand(1), loop) ||
                    BO->getOperand(1) == dynamic_cast<IRValue *>(phi) && LoopInfo::isLoopInvariant(BO->getOperand(0), loop)) {
                    BISet.insert(new BasicInductionVariable(phi, BO, loop));
                }
            }
        } else {
            break;
        }
    }
    return BISet;
}

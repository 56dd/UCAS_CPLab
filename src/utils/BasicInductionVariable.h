#ifndef COMPILER_BASICINDUCTIONVARIABLE_H
#define COMPILER_BASICINDUCTIONVARIABLE_H

#include <set>

class IRValue;

class IRPHINode;

class IRBinaryOperator;

class LoopInfo;

class BasicInductionVariable {
private:
    IRValue *incrementVal{};
    IRValue *baseVal{};
    IRPHINode *phiNode{};
    IRBinaryOperator *calcNode{};
    LoopInfo *belongsTo{};
public:
    BasicInductionVariable(IRPHINode *phi, IRBinaryOperator *BO, LoopInfo *loopInfo);

    static std::set<BasicInductionVariable *> findBasicInductionVar(LoopInfo *loop);

    IRValue *getIncrementVal() const;

    IRPHINode *getPhiNode() const;

    IRBinaryOperator *getCalcNode() const;

    LoopInfo *getBelongsTo() const;

    IRValue *getBaseVal() const;
};


#endif //COMPILER_BASICINDUCTIONVARIABLE_H

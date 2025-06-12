#ifndef COMPILER_IOPERATORS_H
#define COMPILER_IOPERATORS_H


#include "InstrTypes.h"

class IRSetCondInst : public IRBinaryOperator {
    BinaryOps OpType;

public:
    IRSetCondInst(BinaryOps Opcode, IRValue *LHS, IRValue *RHS,
                  const std::string &Name = "", IRBasicBlock *parent = nullptr);

    /// getInverseCondition - Return the inverse of the current condition opcode.
    /// For example seteq -> setne, setgt -> setle, setlt -> setge, etc...
    ///
    BinaryOps getInverseCondition() const {
        return getInverseCondition(getOpcode());
    }

    /// getInverseCondition - Static version that you can use without an
    /// instruction available.
    ///
    static BinaryOps getInverseCondition(BinaryOps Opcode);

    /// getSwappedCondition - Return the condition opcode that would be the result
    /// of exchanging the two operands of the setcc instruction without changing
    /// the result produced.  Thus, seteq->seteq, setle->setge, setlt->setgt, etc.
    ///
    BinaryOps getSwappedCondition() const {
        return getSwappedCondition(getOpcode());
    }

    /// getSwappedCondition - Static version that you can use without an
    /// instruction available.
    ///
    static BinaryOps getSwappedCondition(BinaryOps Opcode);


    // Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const IRSetCondInst *) { return true; }
    static inline bool classof(const IRInstruction *I) {
        return I->getOpcode() == SetEQ || I->getOpcode() == SetNE ||
               I->getOpcode() == SetLE || I->getOpcode() == SetGE ||
               I->getOpcode() == SetLT || I->getOpcode() == SetGT;
    }
};


#endif//COMPILER_IOPERATORS_H

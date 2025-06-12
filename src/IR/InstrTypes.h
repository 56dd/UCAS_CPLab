#ifndef COMPILER_INSTRTYPES_H
#define COMPILER_INSTRTYPES_H

#include "IRInstruction.h"

class IRTerminatorInst : public IRInstruction {
protected:
    explicit IRTerminatorInst(IRInstruction::TermOps iType, IRBasicBlock *parent = nullptr)
        : IRInstruction(IRType::VoidTy, iType, "", parent) {
    }
    IRTerminatorInst(IRType *Ty, IRInstruction::TermOps iType,
                     const std::string &Name = "", IRBasicBlock *parent = nullptr)
        : IRInstruction(Ty, iType, Name, parent) {
    }

public:
    virtual IRInstruction *clone() const = 0;

    // Terminator instruction must provide the successor block of this block
    virtual const IRBasicBlock *getSuccessor(unsigned idx) const = 0;
    virtual unsigned getNumSuccessors() const = 0;

    virtual void setSuccessor(unsigned idx, IRBasicBlock *B) = 0;

    inline IRBasicBlock *getSuccessor(unsigned idx) {
        return (IRBasicBlock *) ((const IRTerminatorInst *) this)->getSuccessor(idx);
    }

    static inline bool classof(const IRTerminatorInst *) { return true; }
    static inline bool classof(const IRInstruction *I) {
        return I->getOpcode() >= TermOpsBegin && I->getOpcode() < TermOpsEnd;
    }
};

class IRBinaryOperator : public IRInstruction {
protected:
    IRBinaryOperator(BinaryOps iType, IRValue *S1, IRValue *S2, IRType *Ty,
                     const std::string &Name, IRBasicBlock *parent);

public:
    static IRBinaryOperator *create(BinaryOps Op, IRValue *S1, IRValue *S2,
                                    const std::string &Name = "",
                                    IRBasicBlock *parent = nullptr);

    static IRBinaryOperator *createNeg(IRValue *Op, const std::string &Name = "",
                                       IRBasicBlock *parent = nullptr);
    static IRBinaryOperator *createNot(IRValue *Op, const std::string &Name = "",
                                       IRBasicBlock *parent = nullptr);
    static bool isNeg(IRValue *V);
    static bool isNot(IRValue *V);
    static IRValue *getNegArgument(IRBinaryOperator *Bop);
    static IRValue *getNotArgument(IRBinaryOperator *Bop);
    BinaryOps getOpcode() const {
        return (BinaryOps) IRInstruction::getOpcode();
    }

    virtual IRInstruction *clone() const {
        return create(getOpcode(), Operands[0], Operands[1]);
    }
    bool swapOperands();

    static inline bool classof(const IRBinaryOperator *) { return true; }
    static inline bool classof(const IRInstruction *I) {
        return I->getOpcode() >= BinaryOpsBegin && I->getOpcode() < BinaryOpsEnd;
    }
};
#endif//COMPILER_INSTRTYPES_H

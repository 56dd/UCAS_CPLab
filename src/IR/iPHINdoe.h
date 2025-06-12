#ifndef COMPILER_IPHINDOE_H
#define COMPILER_IPHINDOE_H


#include "IRInstruction.h"

class IRBasicBlock;

class IRPHINode : public IRInstruction {
private:
    IRPHINode(const IRPHINode &PN) : IRInstruction(PN.getType(), IRInstruction::PHI) {
        unsigned num = PN.getNumIncomingValues();
        for (int i = 0; i < num; ++i) {
            addIncoming(PN.getIncomingValue(i), getIncomingBlock(i));
        }
    }

    IRAllocaInst *var;
public:
    IRAllocaInst *getVar() const {
        return var;
    }

    explicit IRPHINode(IRType *Ty, IRAllocaInst *var, const std::string &Name = "",
                       IRBasicBlock *InsertBefore = nullptr)
            : IRInstruction(Ty, IRInstruction::PHI, Name, InsertBefore), var(var) {
    }

    unsigned getNumIncomingValues() const { return Operands.size() / 2; }

    /******偶数index是对应的赋值******/
    IRValue *getIncomingValue(unsigned i) const {
        assert(i * 2 < Operands.size() && "Invalid value number!");
        return Operands[i * 2];
    }

    void setIncomingValue(unsigned i, IRValue *V) {
        assert(i * 2 < Operands.size() && "Invalid value number!");
        Operands[i * 2] = V;
    }

    static inline unsigned getOperandNumForIncomingValue(unsigned i) {
        return i * 2;
    }

    IRInstruction *clone() const override {
        return new IRPHINode(*this);
    }

    /******奇数index是对应的basicblock******/
    /// getIncomingBlock - Return incoming basic block #x
    IRBasicBlock *getIncomingBlock(unsigned i) const {
        assert(i * 2 + 1 < Operands.size() && "Invalid value number!");
        return (IRBasicBlock *) Operands[i * 2 + 1].get();
    }

    void setIncomingBlock(unsigned i, IRBasicBlock *BB) {
        assert(i * 2 + 1 < Operands.size() && "Invalid value number!");
        Operands[i * 2 + 1] = (IRValue *) BB;
    }

    static unsigned getOperandNumForIncomingBlock(unsigned i) {
        return i * 2 + 1;
    }

    /******赋值与basicblock同时给进******/
    /// addIncoming - Add an incoming value to the end of the PHI list
    void addIncoming(IRValue *D, IRBasicBlock *BB) {
        assert(getType() == D->getType() &&
               "All operands to PHI node must be the same type as the PHI node!");
        Operands.emplace_back(D, this);
        Operands.emplace_back((IRValue *) BB, this);
    }

    /******根据给定的基本块返回index和对应的value******/
    /// getBasicBlockIndex - Return the first index of the specified basic
    /// block in the value list for this PHI.  Returns -1 if no instance.
    ///
    int getBasicBlockIndex(const IRBasicBlock *BB) const {
        for (unsigned i = 0; i < Operands.size() / 2; ++i)
            if (getIncomingBlock(i) == BB) return i;
        return -1;
    }

    IRValue *getIncomingValueForBlock(const IRBasicBlock *BB) const {
        int idx = getBasicBlockIndex(BB);
        if (idx == -1) {
            return nullptr;
        }
        return getIncomingValue(getBasicBlockIndex(BB));
    }


    /// Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const IRPHINode *) { return true; }

    static inline bool classof(const IRInstruction *I) {
        return I->getOpcode() == IRInstruction::PHI;
    }
};


#endif//COMPILER_IPHINDOE_H

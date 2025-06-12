#ifndef COMPILER_ITERMINATORS_H
#define COMPILER_ITERMINATORS_H

#include "InstrTypes.h"

class IRReturnInst : public IRTerminatorInst {
    IRReturnInst(const IRReturnInst &RI) : IRTerminatorInst(IRInstruction::Ret) {
        if (!RI.Operands.empty()) {
            assert(RI.Operands.size() == 1 && "Return insn can only have 1 operand!");
            Operands.reserve(1);
            Operands.emplace_back(RI.Operands[0], this);
        }
    }

public:
    IRReturnInst(IRValue *RetVal = nullptr, IRBasicBlock *parent = nullptr)
            : IRTerminatorInst(IRInstruction::Ret, parent) {
        if (RetVal) {
            Operands.reserve(1);
            Operands.emplace_back(RetVal, this);
        }
        if (parent && parent->getTerminator() != this) {
            dropAllReferences();
        }
    }

    IRInstruction *clone() const override { return new IRReturnInst(*this); }

    inline IRValue *getReturnValue() const {
        return !Operands.empty() ? Operands[0].get() : nullptr;
    }

    /******Successor******/
    const IRBasicBlock *getSuccessor(unsigned idx) const override {
        assert(0 && "ReturnInst has no successors!");
    }

    void setSuccessor(unsigned idx, IRBasicBlock *NewSucc) override {
        assert(0 && "ReturnInst has no successors!");
    }

    unsigned getNumSuccessors() const override { return 0; }


    // Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const IRReturnInst *) { return true; }

    static inline bool classof(const IRInstruction *I) {
        return (I->getOpcode() == IRInstruction::Ret);
    }
};

class IRBranchInst : public IRTerminatorInst {
    IRBranchInst(const IRBranchInst &BI);

public:
    // If cond = null, then is an unconditional br...
    IRBranchInst(IRBasicBlock *IfTrue, IRBasicBlock *IfFalse, IRValue *cond = nullptr,
                 IRBasicBlock *parent = nullptr);

    explicit IRBranchInst(IRBasicBlock *IfTrue, IRBasicBlock *parent = nullptr);

    virtual IRInstruction *clone() const { return new IRBranchInst(*this); }

    /******是否带有为0判断******/
    inline bool isUnconditional() const { return Operands.size() == 1; }

    inline bool isConditional() const { return Operands.size() == 3; }

    inline IRValue *getCondition() const {
        return isUnconditional() ? nullptr : (IRValue *) Operands[2].get();
    }

    void setCondition(IRValue *V) {
        assert(isConditional() && "Cannot set condition of unconditional branch!");
        setOperand(2, V);
    }

    // setUnconditionalDest - Change the current branch to an unconditional branch
    // targeting the specified block.
    //
    void setUnconditionalDest(IRBasicBlock *Dest) {
        if (isConditional()) Operands.erase(Operands.begin() + 1, Operands.end());
        Operands[0] = (IRValue *) Dest;
    }

    /**是condition那么前两个是基本块标号，最后一个是condition
    是uncondition那么第一个就是基本块标号**/

    /******获得后续块******/
    const IRBasicBlock *getSuccessor(unsigned i) const override {
        assert(i < getNumSuccessors() && "Successor # out of range for Branch!");
        return (i == 0) ? dynamic_cast<IRBasicBlock *>(Operands[0].get())
                        : dynamic_cast<IRBasicBlock *>(Operands[1].get());
    }

    inline IRBasicBlock *getSuccessor(unsigned idx) {
        return (IRBasicBlock *) ((const IRBranchInst *) this)->getSuccessor(idx);
    }

    void setSuccessor(unsigned idx, IRBasicBlock *NewSucc) override {
        assert(idx < getNumSuccessors() && "Successor # out of range for Branch!");
        Operands[idx] = (IRValue *) NewSucc;
    }

    unsigned getNumSuccessors() const override { return 1 + isConditional(); }

    // Methods for support type inquiry through isa, cast, and dyn_cast:
    static inline bool classof(const IRBranchInst *) { return true; }

    static inline bool classof(const IRInstruction *I) {
        return (I->getOpcode() == IRInstruction::Br);
    }
};

#endif//COMPILER_ITERMINATORS_H

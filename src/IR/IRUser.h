#ifndef COMPILER_IRUSER_H
#define COMPILER_IRUSER_H

#include <cassert>

#include "IRUse.h"
#include "IRValue.h"

class IRUse;

class IRUser : public IRValue {
protected:
    std::vector<IRUse> Operands;

public:
    IRUser(IRType *Ty, ValueTy vty, const std::string &name = "");

    /******根据index获得偏移******/
    inline IRValue *getOperand(unsigned i) const {
        assert(i < Operands.size() && "getOperand() out of range!");
        return Operands[i];
    }

    inline void setOperand(unsigned i, IRValue *Val) {
        assert(i < Operands.size() && "setOperand() out of range!");
        Operands[i] = Val;
    }

    /******获得操作数个数******/
    inline unsigned getNumOperands() const { return Operands.size(); }

    void dropAllReferences() {
        Operands.clear();
    }

    void replaceUsesOfWith(IRValue *From, IRValue *To);

    static inline bool classof(const IRUser *) { return true; }

    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::GlobalVariableVal ||
               V->getValueType() == IRValue::ConstantVal ||
               V->getValueType() == IRValue::InstructionVal;
    }
};


#endif//COMPILER_IRUSER_H

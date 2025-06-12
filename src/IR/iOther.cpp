#include "iOther.h"

#include "IRDerivedTypes.h"
#include "IRFunction.h"

IRCallInst::IRCallInst(IRValue *F, const std::vector<IRValue *> &Par, const std::string &Name, IRBasicBlock *parent)
    : IRInstruction(dynamic_cast<IRFunction *>(F)->getFunctionType()->getReturnType(),
                    IRInstruction::Call, Name, parent) {
    Operands.reserve(1 + Par.size());
    Operands.emplace_back(F, this);

    for (auto par: Par) {
        Operands.emplace_back(par, this);
    }
}

IRCallInst::IRCallInst(IRValue *F, const std::string &Name, IRBasicBlock *parent)
    : IRInstruction(dynamic_cast<IRFunctionType *>(F)->getReturnType(),
                    IRInstruction::Call, Name, parent) {
    Operands.reserve(1);
    Operands.emplace_back(F, this);
}

IRCallInst::IRCallInst(IRValue *F, IRValue *Actual, const std::string &Name, IRBasicBlock *parent)
    : IRInstruction(dynamic_cast<IRFunctionType *>(F)->getReturnType(),
                    IRInstruction::Call, Name, parent) {
    Operands.reserve(2);
    Operands.emplace_back(F, this);

    Operands.emplace_back(Actual, this);
}

IRCallInst::IRCallInst(const IRCallInst &CI)
    : IRInstruction(CI.getType(), IRInstruction::Call) {
    Operands.reserve(CI.Operands.size());
    for (const auto &Operand: CI.Operands)
        Operands.emplace_back(Operand, this);
}

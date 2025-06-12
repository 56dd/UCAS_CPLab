#include "iOperators.h"

#include "IRBasicBlock.h"
#include "IRConstant.h"
#include "IRType.h"
#include "InstrTypes.h"


IRBinaryOperator::IRBinaryOperator(BinaryOps iType, IRValue *S1, IRValue *S2, IRType *Ty, const std::string &Name, IRBasicBlock *parent)
    : IRInstruction(Ty, iType, Name, parent) {
    Operands.reserve(2);
    Operands.emplace_back(S1, this);
    Operands.emplace_back(S2, this);
}

IRBinaryOperator *IRBinaryOperator::create(BinaryOps Op, IRValue *S1, IRValue *S2, const std::string &Name, IRBasicBlock *parent) {
    switch (Op) {
        // Binary comparison operators...
        case SetLT:
        case SetGT:
        case SetLE:
        case SetGE:
        case SetEQ:
        case SetNE:
            return new IRSetCondInst(Op, S1, S2, Name, parent);

        default:
            if (S1->getType()->isDerivedType())
                return new IRBinaryOperator(Op, S1, S2, S1->getType(), Name, parent);
            else
                return new IRBinaryOperator(Op, S1, S2, S2->getType(), Name, parent);
    }
}

IRBinaryOperator *IRBinaryOperator::createNeg(IRValue *Op, const std::string &Name, IRBasicBlock *parent) {
    return new IRBinaryOperator(IRInstruction::Sub,
                                IRConstant::getNullValue(Op->getType()), Op, Op->getType(), Name, parent);
}

IRBinaryOperator *IRBinaryOperator::createNot(IRValue *Op, const std::string &Name, IRBasicBlock *parent) {
    return new IRBinaryOperator(IRInstruction::Xor,
                                IRConstant::getAllOnesValue(Op->getType()), Op, Op->getType(), Name, parent);
}

bool IRBinaryOperator::isNeg(IRValue *V) {
    if (const IRBinaryOperator *Bop = dynamic_cast<IRBinaryOperator *>(V))
        return Bop->getOpcode() == IRInstruction::Sub &&
               Bop->getOperand(0) == IRConstant::getNullValue(Bop->getType());
    return false;
}

bool IRBinaryOperator::isNot(IRValue *V) {
    if (const IRBinaryOperator *Bop = dynamic_cast<IRBinaryOperator *>(V))
        return (Bop->getOpcode() == IRInstruction::Xor &&
                (Bop->getOperand(1) == IRConstant::getAllOnesValue(Bop->getType()) ||
                 Bop->getOperand(0) == IRConstant::getAllOnesValue(Bop->getType())));
    return false;
}

IRValue *IRBinaryOperator::getNegArgument(IRBinaryOperator *Bop) {
    return Bop->getOperand(1);
}

IRValue *IRBinaryOperator::getNotArgument(IRBinaryOperator *Bop) {
    IRValue *Op0 = Bop->getOperand(0);
    IRValue *Op1 = Bop->getOperand(1);

    if (Op0 == IRConstant::getAllOnesValue(Bop->getType())) {
        return Op1;
    }

    return Op0;
}

bool IRBinaryOperator::swapOperands() {
    if (isCommutative())
        ;
    else if (auto *SCI = dynamic_cast<IRSetCondInst *>(this)) {
        iType = SCI->getSwappedCondition();
    } else
        return true;

    std::swap(Operands[0], Operands[1]);
    return false;
}

IRSetCondInst::IRSetCondInst(BinaryOps Opcode, IRValue *LHS, IRValue *RHS, const std::string &Name, IRBasicBlock *parent)
    : IRBinaryOperator(Opcode, LHS, RHS, IRType::BoolTy, Name, parent) {
    OpType = Opcode;
}
IRInstruction::BinaryOps IRSetCondInst::getInverseCondition(IRInstruction::BinaryOps Opcode) {
    switch (Opcode) {
        default:
            assert(0 && "Unknown setcc opcode!");
        case SetEQ:
            return SetNE;
        case SetNE:
            return SetEQ;
        case SetGT:
            return SetLE;
        case SetLT:
            return SetGE;
        case SetGE:
            return SetLT;
        case SetLE:
            return SetGT;
    }
}
IRInstruction::BinaryOps IRSetCondInst::getSwappedCondition(IRInstruction::BinaryOps Opcode) {
    switch (Opcode) {
        default:
            assert(0 && "Unknown setcc instruction!");
        case SetEQ:
        case SetNE:
            return Opcode;
        case SetGT:
            return SetLT;
        case SetLT:
            return SetGT;
        case SetGE:
            return SetLE;
        case SetLE:
            return SetGE;
    }
}

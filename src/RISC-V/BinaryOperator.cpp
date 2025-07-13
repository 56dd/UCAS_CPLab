#include "BinaryOperator.h"

#include "IR/IRValue.h"
#include "Value.h"
#include "IR/IRType.h"

namespace RISCV {

    BinaryOperator::BinaryOperator(unsigned int iType, IRType *ty, Value *rd, Value *op1, Value *op2,
                                   BasicBlock *parent)
            : Instruction(IRType::VoidTy, iType, parent), ty(ty) {
        Operands.push_back(rd);
        Operands.push_back(op1);
        Operands.push_back(op2);
    }

    void BinaryOperator::print(std::ostream &O) const {
        assert(ty == IRType::BoolTy || ty == IRType::IntTy || ty == IRType::FloatTy ||
               ty == IRType::DoubleTy && "Error type");
        if (ty == IRType::DoubleTy || ty == IRType::FloatTy) {
            O << "f";
        }
        switch (iType) {
            case Add:
                O << "add";
                break;
            case Addi:
                O << "addi";
                break;
            case Sub:
                O << "sub";
                break;
            case Mul:
                O << "mul";
                break;
            case Div:
                O << "div";
                break;
            case Rem:
                O << "rem";
                break;
            case Xori:
                O << "xori";
                break;
            default:
                assert(0 && "Error iType");
        }
        if (ty == IRType::FloatTy) {
            O << ".s";
        } else if (ty == IRType::DoubleTy) {
            O << ".d";
        }
        O << " ";
        Operands[0]->print(O);
        O << ", ";
        Operands[1]->print(O);
        O << ", ";
        Operands[2]->print(O);
        O << std::endl;
    }


} // RISCV
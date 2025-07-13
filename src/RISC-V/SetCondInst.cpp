#include "SetCondInst.h"

#include "IR/IRType.h"
#include "Value.h"

namespace RISCV {
    SetCondInst::SetCondInst(unsigned int iType, Value *rd, Value *op1, Value *op2, BasicBlock *parent)
            : Instruction(IRType::VoidTy, iType, parent) {
        Operands.push_back(rd);
        Operands.push_back(op1);
        Operands.push_back(op2);
    }

    void SetCondInst::print(std::ostream &O) const {
        auto ty = Operands[1]->getIrValue()->getType();
        assert(ty == IRType::FloatTy || ty == IRType::DoubleTy && "Error type");
        switch (iType) {
            case Feq:
                O << "feq";
                break;
            case Fle:
                O << "fle";
                break;
            case Flt:
                O << "flt";
                break;
            default:
                assert(0 && "unknown iType");
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
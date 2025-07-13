#include "MoveInst.h"
#include "IR/IRType.h"
#include "Value.h"

namespace RISCV {
    MoveInst::MoveInst(IRType *ty, Value *dest, Value *src, BasicBlock *parent)
            : Instruction(IRType::VoidTy, Mv, parent), ty(ty) {
        if (ty == IRType::FloatTy || ty == IRType::DoubleTy)
            iType = Fmv;
        Operands.push_back(dest);
        Operands.push_back(src);
    }

    void MoveInst::print(std::ostream &O) const {
        if (ty == IRType::IntTy || ty == IRType::BoolTy || ty->isDerivedType()) {
            O << "mv ";
        } else if (ty == IRType::FloatTy) {
            O << "fmv.s ";
        } else if (ty == IRType::DoubleTy) {
            O << "fmv.d ";
        } else
            assert(0 && "Error ty");
        Operands[0]->print(O);
        O << ", ";
        Operands[1]->print(O);
        O << std::endl;
    }
} // RISCV
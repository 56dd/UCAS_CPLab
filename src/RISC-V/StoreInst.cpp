#include "StoreInst.h"
#include "IR/IRType.h"

namespace RISCV {
    StoreInst::StoreInst(Value *rd, Pointer *ptr, BasicBlock *parent, IRType *ty, Value *rt)
            : Instruction(IRType::VoidTy, 0, parent), rt(rt) {
        assert(ty != IRType::VoidTy && ty != IRType::LabelTy && ty != IRType::TypeTy && "Error Type");
        if (ty == nullptr || ty->getPrimitiveID() == IRType::PointerTyID)
            iType = Sd;
        else if (ty == IRType::BoolTy)
            iType = Sb;
        else if (ty == IRType::IntTy)
            iType = Sw;
        else if (ty == IRType::FloatTy)
            iType = Fsw;
        else if (ty == IRType::DoubleTy)
            iType = Fsd;
        Operands.push_back(rd);
        Operands.push_back(ptr);
    }

    void StoreInst::print(std::ostream &O) const {
        switch (iType) {
            case Sb:
                O << "sb ";
                break;
            case Sw:
                O << "sw ";
                break;
            case Sd:
                O << "sd ";
                break;
            case Fsw:
                O << "fsw ";
                break;
            case Fsd:
                O << "fsd ";
                break;
            default:
                assert(0 && "Unknown iType");
        }
        Operands[0]->print(O);
        O << ", ";
        Operands[1]->print(O);
        if (dynamic_cast<Pointer *>(Operands[1])->isSymbol1()) {
            assert(rt && "miss rt");
            O << ", ";
            rt->print(O);
        }
        O << std::endl;
    }
} // RISCV
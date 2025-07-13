#include "LoadInst.h"
#include "IR/IRType.h"

namespace RISCV {
    LoadInst::LoadInst(Value *rd, Pointer *ptr, BasicBlock *parent, IRType *ty, Value *rt)
            : Instruction(IRType::VoidTy, 0, parent), rt(rt) {
        assert(ty != IRType::VoidTy && ty != IRType::LabelTy && ty != IRType::TypeTy && "Error Type");
        if (ty == nullptr || ty->getPrimitiveID() == IRType::PointerTyID)
            iType = Ld;
        else if (ty == IRType::BoolTy)
            iType = Lb;
        else if (ty == IRType::IntTy)
            iType = Lw;
        else if (ty == IRType::FloatTy)
            iType = Flw;
        else if (ty == IRType::DoubleTy)
            iType = Fld;
        else
            iType = La;
        Operands.push_back(rd);
        Operands.push_back(ptr);
    }

    void LoadInst::print(std::ostream &O) const {
        switch (iType) {
            case Lb:
                O << "lb ";
                break;
            case Lw:
                O << "lw ";
                break;
            case Ld:
                O << "ld ";
                break;
            case La:
                O << "la ";
                break;
            case Flw:
                O << "flw ";
                break;
            case Fld:
                O << "fld ";
                break;
            default:
                assert(0 && "Unknown iType");
        }
        Operands[0]->print(O);
        O << ", ";
        Operands[1]->print(O);
        if (dynamic_cast<Pointer *>(Operands[1])->isSymbol1() && (iType == Fld || iType == Flw)) {
            assert(rt && "miss rt");
            O << ", ";
            rt->print(O);
        }
        O << std::endl;
    }

} // RISCV
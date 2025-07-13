#include "Value.h"
#include "IR/IRValue.h"
#include "BasicBlock.h"
#include "utils/Register.h"
#include "Function.h"
#include "IR/IRType.h"

namespace RISCV {
    Register *Value::getReg() const {
        return reg;
    }

    IRValue *Value::getIrValue() const {
        return irValue;
    }

    Value::Value(Register *Reg, IRType *type) : reg(Reg), ty(type) {
    }

    Value::Value(IRValue *irV) : irValue(irV), reg(irV->getReg()), ty(irV->getType()) {
    }

    Value::Value(int val) : val(val), ty(IRType::IntTy) {
    }


    int Value::getVal() const {
        return val;
    }

    void Value::print(std::ostream &O) {
        if (reg) {
            O << reg->getRegName();
        } else if (BB) {
            O << BB->getName();
        } else if (F) {
            O << F->getName();
        } else {
            O << val;
        }
    }

    Value::Value(BasicBlock *BB) : BB(BB), ty(IRType::VoidTy) {
    }

    Value::Value(Function *F) : F(F), ty(IRType::VoidTy) {
    }

    IRType *Value::getTy() const {
        return ty;
    }

    Pointer::Pointer(int offset, Register *reg) : Value(), offset(offset) {
        ty = IRType::IntTy;
        base = reg;
    }

    void Pointer::print(std::ostream &O) {
        if (var) {
            O << var->getName() << "_obj";
        } else {
            O << offset << "(" << base->getRegName() << ")";
        }
    }

    int Pointer::getOffset() const {
        return offset;
    }

    Pointer::Pointer(GlobalVariable *var) : Value(), var(var) {
        isSymbol = true;
    }

    bool Pointer::isSymbol1() const {
        return isSymbol;
    }

    Register *Pointer::getBase() const {
        return base;
    }

} // RISCV
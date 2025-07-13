#ifndef COMPILER_VALUE_H
#define COMPILER_VALUE_H

#include <iostream>
#include "IR/IRType.h"
#include "utils/Register.h"
#include "GlobalVariable.h"

class Register;

class IRValue;

class IRType;

namespace RISCV {

    class BasicBlock;

    class Function;

    class Value {
    private:
        IRValue *irValue = nullptr;
        Register *reg = nullptr;
        int val = 0;
        BasicBlock *BB = nullptr;
        Function *F = nullptr;
    protected:
        IRType *ty;
    public:
        Value() = default;

        explicit Value(IRValue *irV);

        Value(Register *Reg, IRType *type = IRType::IntTy);

        explicit Value(int val);

        explicit Value(BasicBlock *BB);

        explicit Value(Function *F);

        Register *getReg() const;

        IRValue *getIrValue() const;

        int getVal() const;

        IRType *getTy() const;

        virtual void print(std::ostream &O);
    };

    class Pointer : public Value {
    private:
        int offset = 0;

        GlobalVariable *var = nullptr;

        Register *base = nullptr;

        bool isSymbol = false;
    public:

        explicit Pointer(int offset, Register *reg = CalleeSavedRegister::sp);

        explicit Pointer(GlobalVariable *var);

        void print(std::ostream &O) override;

        int getOffset() const;

        bool isSymbol1() const;

        Register *getBase() const;
    };

} // RISCV

#endif //COMPILER_VALUE_H

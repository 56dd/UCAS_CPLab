#ifndef COMPILER_IRGLOBALVARIABLE_H
#define COMPILER_IRGLOBALVARIABLE_H
#pragma once

#include <cassert>

#include "IRGlobalValue.h"
#include "IRModule.h"

class IRModule;

class IRGlobalVariable : public IRGlobalValue {
    void setParent(IRModule *parent);

    bool isConstantGlobal;

    bool isinitial;

public:
    IRGlobalVariable(IRType *Ty, bool isConstant, LinkageTypes Linkage,
                     IRConstant *Initializer = nullptr, const std::string &Name = "",
                     IRModule *Parent = nullptr, bool isinitial = true);

    /******全局变量的初始化******/
    inline bool hasInitializer() const { return !Operands.empty(); }
    inline IRConstant *getInitializer() const {
        assert(hasInitializer() && "GV doesn't have initializer!");
        return (IRConstant *) Operands[0].get();
    }
    inline void setInitializer(IRConstant *CPV) {
        if (CPV == nullptr) {
            if (hasInitializer()) Operands.pop_back();
        } else {
            if (!hasInitializer()) Operands.emplace_back(nullptr, this);
            Operands[0] = (IRValue *) CPV;
        }
    }

    /******判断是不是一个常量，但是我们都会把这个常量直接当作立即数使用，故无用******/
    bool isConstant() const { return isConstantGlobal; }

    bool isIsinitial() const;

    /******全局变量的print******/
    void printPrefixName(std::ostream &OS) const;
    void print(std::ostream &OS) const override;

    /******判断是全局变量还是函数******/
    static inline bool classof(const IRGlobalVariable *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::GlobalVariableVal;
    }
};

#endif//COMPILER_IRGLOBALVARIABLE_H

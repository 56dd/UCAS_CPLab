#ifndef COMPILER_IRARGUMENT_H
#define COMPILER_IRARGUMENT_H
#pragma once

#include "utils/Register.h"
#include "utils/RegisterNode.h"
#include "IRFunction.h"
#include "IRValue.h"

class IRValue;
class IRFunction;
class RegisterNode;
class Register;

class IRArgument : public IRValue {
private:
    IRFunction *Parent = nullptr;
    RegisterNode* regNode = nullptr;
    Register* reg;

public:
    explicit IRArgument(IRType *Ty, const std::string &Name = "", IRFunction *F = nullptr);
    ~IRArgument() override = default;

    /******IRArgument的母函数******/
    void setParent(IRFunction *parent);
    inline IRFunction *getParent() { return Parent; }

    /******IRArgument的print方法******/
    void printPrefixName(std::ostream &OS) const override;
    void print(std::ostream &OS) const override;

    RegisterNode* getRegNode(){ return regNode; };

    void setRegNode(){ if( regNode == nullptr ) regNode = new RegisterNode(this->getName(), this); };

    void setReg(Register* reg){
        this->reg = reg;
    };

    Register* getReg() override{ return reg; };

    /******classof方法，判断从父类下来的子类是不是对应的IRArgument类******/
    static inline bool classof(const IRArgument *) { return true; }
    static inline bool classof(const IRValue *V) {
        return V->getValueType() == ArgumentVal;
    }
};


#endif//COMPILER_IRARGUMENT_H

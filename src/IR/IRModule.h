#ifndef COMPILER_IRMODULE_H
#define COMPILER_IRMODULE_H
#pragma once

#include <string>
#include <vector>

#include "IRFunction.h"
#include "IRGlobalVariable.h"

class IRGlobalVariable;
class FunctionType;

/******最上层的IR******/
class IRModule {
private:
    std::string name;
    std::vector<IRFunction *> funcList;
    std::vector<IRGlobalVariable *> varList;

public:
    explicit IRModule(std::string name);

    void setName(std::string &Name){ name = Name; };
    std::string &getName(){ return name; };

    /******添加全局变量以及函数******/
    void addGlobalVariable(IRGlobalVariable *var);
    void addFunction(IRFunction *func);

    IRFunction *getFunction(const std::string &name);

    IRFunction *getMainFunction();

    const std::vector<IRFunction *> &getFuncList() const;

    const std::vector<IRGlobalVariable *> &getVarList() const;

    /******print方法******/
    void print(std::ostream &OS);
};


#endif//COMPILER_IRMODULE_H

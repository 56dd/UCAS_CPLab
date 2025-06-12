#include "IRModule.h"
#include "IR/IRValue.h"
#include <iostream>

#include <utility>
IRModule::IRModule(std::string name) : name(std::move(name)) {
}
void IRModule::addGlobalVariable(IRGlobalVariable *var) {
    varList.push_back(var);
}
void IRModule::addFunction(IRFunction *func) {
    funcList.push_back(func);
}
void IRModule::print(std::ostream &OS) {

    /******打印module_name******/
    OS << "; ModuleID = " << "\'" << this->name << "\'" << std::endl;
    OS << "source_filename = " << "\"" << this->name << "\"" << std::endl;

    /******打印全局变量******/
    if(!this->varList.empty())
        OS << std::endl;
    for(auto var:this->varList){
        var->print(OS);
    }

    /******打印函数******/
    for(auto func:this->funcList){
        if(func->getFuntTy() == IRFunction::Declared){
            OS << std::endl;
            func->print(OS);
        }
    }
    // TODO
}
IRFunction *IRModule::getFunction(const std::string& name) {
    for (auto func : funcList) {
        if (name == func->getName()) {
            return func;
        }
    }
        return nullptr;
}
IRFunction *IRModule::getMainFunction() {
    return getFunction("main");
}

const std::vector<IRFunction *> &IRModule::getFuncList() const {
    return funcList;
}

const std::vector<IRGlobalVariable *> &IRModule::getVarList() const {
    return varList;
}

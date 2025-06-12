#include "IRGlobalVariable.h"
#include "IR/IRDerivedTypes.h"
#include "IRConstant.h"
#include <iostream>
void IRGlobalVariable::setParent(IRModule *parent) {
    Parent = parent;
}

/**
这里调用globalvarible的print，只会在module中初始化全局变量时进行调用打印，原因在于最终在instruction中进行调用打印
的时候规范与这里不尽相同(那个地方只用调用value中name的打印和直接type的打印)
**/
void IRGlobalVariable::printPrefixName(std::ostream &OS) const{
    OS << "@" << this->getName();
}

void IRGlobalVariable::print(std::ostream &OS) const {
    // TODO
    /******打印module_name******/
    this->printPrefixName(OS);
    OS << " = global ";
    if(this->Linkage == AppendingLinkage)
        OS << "privateFuncVarArray ";
    else if(this->Linkage == ExternalLinkage)
        OS << "externalFuncConstArray ";
    this->getInitializer()->print(OS);//获得初始化use的value值，并进行打印

    //这里的gettype获得的必然是一个pointtype，我在这里通过这个函数去获得它的elementtype，
    //然后看他实际上是一个什么样的类型，在栈中需要分配多大的空间，来打印align
    this->getType()->IRpointerPrintAlign(OS);
    OS << std::endl;
}

//对于一个全局变量他是一个指针类或数组
IRGlobalVariable::IRGlobalVariable(IRType *Ty, bool isConstant, IRGlobalValue::LinkageTypes Linkage, IRConstant *Initializer, const std::string &Name, IRModule *Parent, bool isinitial)
    : IRGlobalValue(new IRPointerType(Ty), IRValue::GlobalVariableVal, Linkage, Name), isConstantGlobal(isConstant), isinitial(isinitial) {
    if (Initializer) {
        Operands.emplace_back(dynamic_cast<IRValue *>(Initializer), this);
    }
    if (Parent) {
        Parent->addGlobalVariable(this);
    }
}

bool IRGlobalVariable::isIsinitial() const {
    return isinitial;
}

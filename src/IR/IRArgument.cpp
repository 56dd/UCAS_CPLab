#include "IRArgument.h"
#include "IR/IRDerivedTypes.h"
#include "IR/IRType.h"
#include <iostream>
#include <ostream>
#include <utils/ErrorHandler.h>

void IRArgument::setParent(IRFunction *parent) {
    Parent = parent;
}

IRArgument::IRArgument(IRType *Ty, const std::string &Name, IRFunction *F)
    : IRValue(Ty, IRValue::ArgumentVal, Name) {
    Parent = nullptr;
    if (F) {
        F->addArgument(this);
    }
}
void IRArgument::printPrefixName(std::ostream &OS) const{
    OS << "%" << this->getName();
}
void IRArgument::print(std::ostream &OS) const {
    this->getType()->print(OS);//调用这个value中的type的print方法
    this->printPrefixName(OS);
    // TODO
}

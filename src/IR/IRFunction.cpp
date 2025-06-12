#include "IRFunction.h"

#include <iostream>

#include "IR/IRArgument.h"
#include "IRModule.h"
#include "utils/Register.h"

void IRFunction::setParent(IRModule *parent) {
    Parent = parent;
}

void IRFunction::printPrefixName(std::ostream &OS) const {
    OS << "@" << this->getName();
}

void IRFunction::Funcprint(std::ostream &OS) const {
    this->getFunctionType()->print(OS);
    this->printPrefixName(OS);

    /******打印arg******/
    OS << "(";
    for (auto arg: ArgumentList) {
        arg->print(OS);
        OS << ", ";
    }
    // 如果参数列表不空回退2个字符
    if (!ArgumentList.empty())
        OS.seekp(static_cast<std::streampos>(static_cast<std::streamoff>(OS.tellp()) - 2));
    OS << ")";

}

void IRFunction::print(std::ostream &OS) const {
    // TODO

    /******打印function开始标识？******/
    OS << "; Function" << std::endl;

    /******打印function本身******/
    OS << "define ";
    this->Funcprint(OS);

    /******打印basciblock******/
    OS << " {" << std::endl;
    for (auto basicblock: BasicBlocks) {
        basicblock->print(OS);
        if (basicblock != BasicBlocks.back()) {
            OS << std::endl;
        }
    }
    OS << "}" << std::endl;

    /*先打印再检查*/
    // RegisterFactory::print(OS, *const_cast<IRFunction*>(this));
    RegisterFactory::check(*const_cast<IRFunction *>(this));
}

//这里无法传一个primitiveType的Ty进来，因为在进来之前必须对IRFunctionType给一系列参数进行初始化
IRFunction::IRFunction(IRFunctionType *Ty, IRGlobalValue::LinkageTypes Linkage, const std::string &N, IRModule *M,
                       IRFunction::FuncTy fty)
        : IRGlobalValue(Ty, IRValue::FunctionVal, Linkage, N) {
    Parent = M;
    fTy = fty;
    /*for (unsigned i = 0, e = args.size(); i < e; ++i) {
        ArgumentList.push_back(new IRArgument(Ty->getParamType(i)));
    }*/
    if (M) {
        M->addFunction(this);
    }
}

void IRFunction::addArgument(IRArgument *arg) {
    ArgumentList.push_back(arg);
}

IRFunctionType *IRFunction::getFunctionType() const {
    return dynamic_cast<IRFunctionType *>(getOriginType());
}

/*const IRType *IRFunction::getReturnType() const {
    return getFunctionType()->getReturnType();
}*/
void IRFunction::addBasicBlock(IRBasicBlock *block) {
    BasicBlocks.push_back(block);
}

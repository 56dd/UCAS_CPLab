#include "Module.h"
#include "GlobalVariable.h"
#include "IR/IRModule.h"
#include "Function.h"

namespace RISCV {
    void Module::addGlobalVariable(GlobalVariable *GV) {
        globalVariableList.push_back(GV);
        globalVariableMap[GV->getIrGv()] = GV;
    }

    Module::Module(IRModule *ir) : labelCount(0) {
        // add global variable
        for (auto irGV: ir->getVarList()) {
            new GlobalVariable(irGV, this);
        }
        // add function
        for (auto irFunc: ir->getFuncList()) {
            if (irFunc->getFuntTy() == IRFunction::UnDeclared)
                IOFunctionList.push_back(new Function(irFunc->getName()));
            else
                new Function(irFunc, this);
        }
    }

    void Module::print(std::ostream &O) {
        // print GlobalVariable
        for (auto GV: globalVariableList) {
            GV->print(O);
        }
        // print function
        for (auto func: functionList) {
            func->print(O);
        }
    }

    unsigned int Module::getLabelCount() {
        return labelCount++;
    }

    void Module::addFunction(Function *F) {
        functionList.push_back(F);
    }

    GlobalVariable *Module::findGlobalVariable(IRGlobalVariable *irGV) {
        return globalVariableMap[irGV];
    }

    Function *Module::findFunction(IRFunction *irF) {
        for (auto func: functionList) {
            if (func->getName() == irF->getName())
                return func;
        }
        for (auto func: IOFunctionList) {
            if (func->getName() == irF->getName())
                return func;
        }
        assert(0 && "Error func");
    }
} // RISCV
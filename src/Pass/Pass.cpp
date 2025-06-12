#include "Pass.h"
#include "IR/IRModule.h"

void FunctionPass::run(IRModule &M) {
    auto funcList = M.getFuncList();
    for (auto func: funcList) {
        if (func->getFuntTy() == IRFunction::Declared)
            runOnFunction(*func);
    }
}

void BasicBlockPass::runOnFunction(IRFunction &F) {
    auto BBList = F.getBasicBlockList();
    for (auto BB: BBList) {
        runOnBasicBlock(*BB);
    }
}

void Pass::addToOpt(Optimizer &opt) {
    opt.addPass(this);
}

Pass::Pass(std::string name, int level) : name(name), level(level) {

}

int Pass::getLevel() const {
    return level;
}

FunctionPass::FunctionPass(std::string name, int level) : Pass(std::move(name), level) {

}

BasicBlockPass::BasicBlockPass(std::string name, int level) : FunctionPass(std::move(name), level) {

}

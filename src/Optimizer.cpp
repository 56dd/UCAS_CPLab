#include "Optimizer.h"
#include "Pass/RenamePass.h"
#include "Pass/CutDeadBlockPass.h"
#include "Pass/MemToRegPass.h"
#include "Pass/AlgebraicPass.h"
#include "Pass/ConstantPass.h"
#include "Pass/LocalSubExpPass.h"
#include "Pass/HoistingLoopInvariantValuePass.h"
#include "Pass/StrengthReductionPass.h"
#include "Pass/GlobalSubExpPass.h"
#include "Pass/CutDeadCodePass.h"
#include "Pass/EliminateBasicInductionVarPass.h"
#include "Pass/RegisterPass.h"
#include "Pass/AggressiveDeadCodeEliminatePass.h"
#include "Pass/PHIdeletePass.h"
#include "Pass/DeleteNonepredsPass.h"

void Optimizer::run() {
    for (auto pass: passList) {
        if (level >= pass->getLevel())
            pass->run(*ir);
    }
}

Optimizer::Optimizer(IRModule *ir)
        : ir(ir), passList(), level(0) {

}

void Optimizer::addPass(Pass *pass) {
    passList.push_back(pass);
}

void Optimizer::build() {
    addPass(new MemToRegPass("Mem2Reg"));

    addPass(new HoistingLoopInvariantValuePass("HoistingLoopInvariantValue"));
    addPass(new ConstantPass("ConstantPass"));
    addPass(new LocalSubExpPass("LocalSubExpPass"));
    addPass(new GlobalSubExpPass("GlobalSubExpPass"));

    addPass(new DeleteNonePredsPass("DeleteNonepredsPass"));

    addPass(new AggressiveDeadCodeEliminatePass("AggressiveDeadCodeEliminate"));

//    new StrengthReductionPass("");
//    new CutDeadCodePass("");
//    new AlgebraicPass("");
//    new EliminateBasicInductionVarPass("");

    addPass(new PHIdeletePass("PHIdeletePass"));

    addPass(new CutDeadBlockPass("CutDeadBLock"));

    addPass(new RenamePass("RenamePass"));

    addPass(new RegisterPass("RegisterPass"));
}

void Optimizer::setLevel(int level) {
    this->level = level;
}

#include "RenamePass.h"
#include "IR/iPHINdoe.h"
#include "IR/iMemory.h"
#include "IR/iOther.h"

#include <utility>

RenamePass::RenamePass(std::string name, int level) : FunctionPass(std::move(name), level) {

}

void RenamePass::runOnFunction(IRFunction &F) {
    F.setCount(0);
    auto ArgList = F.getArgumentList();
    auto BBList = F.getBasicBlockList();
    for (auto arg: ArgList) {
        arg->setName(std::to_string(F.getCount()));
        F.addCount();
    }
    for (auto BB: BBList) {
        BB->setName(std::to_string(F.getCount()));
        F.addCount();
        auto InstList = BB->getInstList();
        for (auto inst: InstList) {
            if (IRStoreInst::classof(inst) ||
                IRMemcpyInst::classof(inst) ||
                IRCallInst::classof(inst) && dynamic_cast<IRCallInst *>(inst)->getType() == IRType::VoidTy) {
                continue;
            }
            if (IRMoveInst::classof(inst)) {
                auto dest = dynamic_cast<IRMoveInst *>(inst)->getDest();
                if (dest->getName().empty()) {
                    dest->setName(std::to_string(F.getCount()));
                    F.addCount();
                }
            } else {
                inst->setName(std::to_string(F.getCount()));
                F.addCount();
            }
        }
    }
}

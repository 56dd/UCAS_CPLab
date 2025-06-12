#include "CutDeadCodePass.h"

#include <utility>

CutDeadCodePass::CutDeadCodePass(std::string name, int level) : FunctionPass(std::move(name), level) {

}

void CutDeadCodePass::runOnFunction(IRFunction &F) {
    bool codeChanged = true;
    std::vector<IRInstruction *> bin;
    while (codeChanged) {
        codeChanged = false;
        auto BBList = F.getBasicBlockList();
        for (auto BB: BBList) {
            auto &instList = BB->getInstList();
            for (auto inst: instList) {
                auto uses = inst->getUses();
                auto opcode = inst->getOpcode();
                bool mayWithoutUse = false;
                switch (opcode) {
                    case IRInstruction::Ret:
                    case IRInstruction::Br:
                    case IRInstruction::Store:
                    case IRInstruction::Memcpy:
                    case IRInstruction::Call:
                        mayWithoutUse = true;
                        break;
                    default:
                        mayWithoutUse = false;
                        break;
                }
                if (uses.empty() && !mayWithoutUse) {
                    codeChanged = true;
                    bin.push_back(inst);
                }
            }
            for (auto trash: bin) {
                trash->dropAllReferences();
                instList.erase(std::find(instList.begin(), instList.end(), trash));
            }
            bin.clear();
        }
    }
}
#include "PHIdeletePass.h"
#include "IR/IRInstruction.h"
#include "IR/iOther.h"
#include "IR/iPHINdoe.h"
#include "utils/LiveVariable.h"
#include <algorithm>
#include "IR/iTerminators.h"
#include "IR/iOperators.h"

PHIdeletePass::PHIdeletePass(std::string name, int level) : FunctionPass(std::move(name), level) {

}

void PHIdeletePass::runOnFunction(IRFunction &F) {
    for (auto BB: F.getBasicBlockList()) {
        auto &instList = BB->getInstList();
        for (auto &inst : instList) {
            if (inst->getOpcode() == IRInstruction::PHI) {
                auto phiInst = dynamic_cast<IRPHINode *>(inst);
                auto temp = new IRRegValue(phiInst->getType());
                temp->dropAllReferences();
                for (unsigned i = 0; i < phiInst->getNumIncomingValues(); i++) {
                    /*必须保证这个块还是存在的*/
                    if(std::find(F.getBasicBlockList().begin(), F.getBasicBlockList().end(), phiInst->getIncomingBlock(i)) != F.getBasicBlockList().end()){
                        /*add move inst*/
                        auto mvInst = new IRMoveInst(phiInst->getIncomingValue(i), temp);
                        mvInst->setParent(phiInst->getIncomingBlock(i));
                        auto terminator = dynamic_cast<IRBranchInst *>(phiInst->getIncomingBlock(i)->getTerminator());
                        if (terminator && terminator->isConditional() && dynamic_cast<IRSetCondInst *>(terminator->getCondition())->getOperand(0)->getType() == IRType::IntTy) {
                            phiInst->getIncomingBlock(i)->getInstList().insert(
                                phiInst->getIncomingBlock(i)->getInstList().end() - 2,
                                mvInst);
                        } else
                        phiInst->getIncomingBlock(i)->getInstList().insert(
                                phiInst->getIncomingBlock(i)->getInstList().end() - 1,
                                mvInst);
                    }
                }
                /*change phi to move*/
                auto phi2Mv = new IRMoveInst(temp, phiInst);
                phi2Mv->setParent(BB);
                inst = phi2Mv;
            }
        }
    }
}
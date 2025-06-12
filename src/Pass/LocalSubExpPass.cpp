#include "LocalSubExpPass.h"
#include "IR/IRInstruction.h"
#include "IR/IRValue.h"
#include "IR/iMemory.h"

#include <algorithm>
#include <bitset>
#include <cstddef>
#include <string>
#include <utility>

void Localldst(IRBasicBlock &BB) {
    std::vector<IRInstruction*>::iterator ite;
    auto& InstList = BB.getInstList();
    for(ite=InstList.begin(); ite<InstList.end(); ite++){
        if((*ite)->getOpcode() == IRInstruction::Store){
            /*消除前驱所有没有被ld打断的st*/
            for(auto it=ite-1; it>=InstList.begin(); it--){
                auto itinst = *it;
                auto iteinst = *ite;
                /*如果遇到st则消除*/
                if( itinst->getOpcode() == IRInstruction::Store &&
                    dynamic_cast<IRStoreInst*>(itinst)->getOperand(1) == dynamic_cast<IRStoreInst*>(iteinst)->getOperand(1)){
                    itinst->dropAllReferences();
                    InstList.erase(it);
                    itinst->replaceAllUsesWith(iteinst);
                    ite--;
                }else if(itinst->getOpcode() == IRInstruction::Load &&
                        dynamic_cast<IRLoadInst*>(itinst)->getOperand(0) == dynamic_cast<IRStoreInst*>(iteinst)->getOperand(1)){
                    break;
                }
            }
        }else if((*ite)->getOpcode() == IRInstruction::Load){
            /*消除前驱所有没有被st打断的ld*/
            for(auto it=ite+1; it<InstList.end();){
                auto itinst = *it;
                auto iteinst = *ite;
                /*如果遇到load则消除*/
                if( itinst->getOpcode() == IRInstruction::Load && 
                    dynamic_cast<IRLoadInst*>(itinst)->getOperand(0) == dynamic_cast<IRLoadInst*>(iteinst)->getOperand(0)){
                    itinst->dropAllReferences();
                    InstList.erase(it);
                    itinst->replaceAllUsesWith(iteinst);
                }else if(itinst->getOpcode() == IRInstruction::Store &&
                        dynamic_cast<IRStoreInst*>(itinst)->getOperand(1) == dynamic_cast<IRLoadInst*>(iteinst)->getOperand(0)){
                    break;
                }else{
                    it++;
                }
            }
        }   
    }
}

void Localchildren(IRBasicBlock &BB) {
    bool flagEnd = true;//如果这一轮有子表达式消除，那么就需要再走一轮

    while(flagEnd){
        flagEnd = false;
        for(unsigned i=0; i<BB.getInstList().size(); i++){
            for(unsigned j=i+1; j<BB.getInstList().size();){
                IRInstruction* irinst1 = BB.getInstList()[i];
                IRInstruction* irinst2 = BB.getInstList()[j];

                bool flag = false;
                /*满足两者操作类型相同，并且以下几种指令是不可以消除局部公共子表达式的*/
                if( (irinst1->getOpcode() == irinst2->getOpcode()) &&
                    (irinst1->getOpcode() != IRInstruction::Br)    &&
                    (irinst1->getOpcode() != IRInstruction::PHI)   &&
                    (irinst1->getOpcode() != IRInstruction::Load) &&
                    (irinst1->getOpcode() != IRInstruction::Store) &&
                    (irinst1->getOpcode() != IRInstruction::Memcpy) &&
                    (irinst1->getOpcode() != IRInstruction::Call) &&
                    (irinst1->getOpcode() != IRInstruction::Alloca) &&
                    (irinst1->getOpcode() != IRInstruction::Ret)){
                    /*如果是可交换的，则两方都需要进行考虑*/
                    if(irinst1->isCommutative()){
                        if( (irinst1->getOperand(0) == irinst2->getOperand(0) && irinst1->getOperand(1) == irinst2->getOperand(1)) ||
                            (irinst1->getOperand(0) == irinst2->getOperand(1) && irinst1->getOperand(1) == irinst2->getOperand(0))){
                                flag = true;
                            }
                    }else{
                        /*按顺序进行检验*/
                        for(unsigned k=0; k<irinst1->getNumOperands(); k++){
                            if(irinst1->getOperand(k) == irinst2->getOperand(k)){ flag = true; }
                            else{ flag = false; break;}
                        }
                    }
                }

                if(flag){//erase完毕后下一条指令自动上前
                    flagEnd = true;
                    auto ircancelinst = std::find(BB.getInstList().begin(), BB.getInstList().end(), irinst2);
                    irinst2->dropAllReferences();
                    BB.getInstList().erase(ircancelinst);
                    irinst2->replaceAllUsesWith(irinst1);
                }else{
                    j++;
                }
            }
        }
    }
}

void LocalSubExpPass::runOnBasicBlock(IRBasicBlock &BB) {
    Localchildren(BB);
    Localldst(BB);
}

LocalSubExpPass::LocalSubExpPass(std::string name, int level) : BasicBlockPass(name, level) {

}

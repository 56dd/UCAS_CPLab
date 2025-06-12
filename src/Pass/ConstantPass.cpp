#include "ConstantPass.h"
#include "IR/IRConstant.h"
#include "IR/IRInstruction.h"
#include "IR/IRType.h"
#include "IR/IRValue.h"
#include "IR/iTerminators.h"
#include "Pass/Pass.h"
#include <algorithm>
#include <typeinfo>

#include <any>
#include <utility>

/*非bool类型*/
IRConstant* alge(unsigned iType, IRConstant* const1, IRConstant* const2){
    auto tyID = const1->getType()->getPrimitiveID();
    switch(iType){
        case IRInstruction::BinaryOps::Add:
            if(tyID == IRType::IntTyID){ return IRConstantInt::get(dynamic_cast<IRConstantInt*>(const1)->getRawValue()+dynamic_cast<IRConstantInt*>(const2)->getRawValue()); }
            else if(tyID == IRType::FloatTyID){ return IRConstantFloat::get(dynamic_cast<IRConstantFloat*>(const1)->getRawValue()+dynamic_cast<IRConstantFloat*>(const2)->getRawValue()); }
            else if(tyID == IRType::DoubleTyID){ return IRConstantDouble::get(dynamic_cast<IRConstantDouble*>(const1)->getRawValue()+dynamic_cast<IRConstantDouble*>(const2)->getRawValue()); }
        case IRInstruction::BinaryOps::Sub:
            if(tyID == IRType::IntTyID){ return IRConstantInt::get(dynamic_cast<IRConstantInt*>(const1)->getRawValue()-dynamic_cast<IRConstantInt*>(const2)->getRawValue()); }
            else if(tyID == IRType::FloatTyID){ return IRConstantFloat::get(dynamic_cast<IRConstantFloat*>(const1)->getRawValue()-dynamic_cast<IRConstantFloat*>(const2)->getRawValue()); }
            else if(tyID == IRType::DoubleTyID){ return IRConstantDouble::get(dynamic_cast<IRConstantDouble*>(const1)->getRawValue()-dynamic_cast<IRConstantDouble*>(const2)->getRawValue()); }
        case IRInstruction::BinaryOps::Mul:
            if(tyID == IRType::IntTyID){ return IRConstantInt::get(dynamic_cast<IRConstantInt*>(const1)->getRawValue()*dynamic_cast<IRConstantInt*>(const2)->getRawValue()); }
            else if(tyID == IRType::FloatTyID){ return IRConstantFloat::get(dynamic_cast<IRConstantFloat*>(const1)->getRawValue()*dynamic_cast<IRConstantFloat*>(const2)->getRawValue()); }
            else if(tyID == IRType::DoubleTyID){ return IRConstantDouble::get(dynamic_cast<IRConstantDouble*>(const1)->getRawValue()*dynamic_cast<IRConstantDouble*>(const2)->getRawValue()); }
        case IRInstruction::BinaryOps::Div:
            if(tyID == IRType::IntTyID){ return IRConstantInt::get(dynamic_cast<IRConstantInt*>(const1)->getRawValue()/dynamic_cast<IRConstantInt*>(const2)->getRawValue()); }
            else if(tyID == IRType::FloatTyID){ return IRConstantFloat::get(dynamic_cast<IRConstantFloat*>(const1)->getRawValue()/dynamic_cast<IRConstantFloat*>(const2)->getRawValue()); }
            else if(tyID == IRType::DoubleTyID){ return IRConstantDouble::get(dynamic_cast<IRConstantDouble*>(const1)->getRawValue()/dynamic_cast<IRConstantDouble*>(const2)->getRawValue()); }
        case IRInstruction::BinaryOps::Rem:
            if(tyID == IRType::IntTyID){ return IRConstantInt::get(dynamic_cast<IRConstantInt*>(const1)->getRawValue()%dynamic_cast<IRConstantInt*>(const2)->getRawValue()); }
    }
}

/*bool类型*/
IRConstant* judge(unsigned iType, IRConstant* const1, IRConstant* const2){
    switch(iType){
        case IRInstruction::BinaryOps::Xor:
            return IRConstantBool::get(dynamic_cast<IRConstantBool*>(const1)->getRawValue()^dynamic_cast<IRConstantBool*>(const2)->getRawValue());
        case IRInstruction::BinaryOps::Or:
            return IRConstantBool::get(dynamic_cast<IRConstantBool*>(const1)->getRawValue()||dynamic_cast<IRConstantBool*>(const2)->getRawValue());
        case IRInstruction::BinaryOps::And:
            return IRConstantBool::get(dynamic_cast<IRConstantBool*>(const1)->getRawValue()&&dynamic_cast<IRConstantBool*>(const2)->getRawValue());
    }
}

bool setge(unsigned iType, IRConstant* const1, IRConstant* const2){
    auto tyID = const1->getType()->getPrimitiveID();
    switch(iType){
        case IRInstruction::BinaryOps::SetEQ:
            if(tyID == IRType::IntTyID){ return dynamic_cast<IRConstantInt*>(const1)->getRawValue() == dynamic_cast<IRConstantInt*>(const2)->getRawValue(); }
            else if(tyID == IRType::FloatTyID){ return dynamic_cast<IRConstantFloat*>(const1)->getRawValue() == dynamic_cast<IRConstantFloat*>(const2)->getRawValue(); }
            else if(tyID == IRType::DoubleTyID){ return dynamic_cast<IRConstantDouble*>(const1)->getRawValue() == dynamic_cast<IRConstantDouble*>(const2)->getRawValue(); }
            else if(tyID == IRType::BoolTyID){ return dynamic_cast<IRConstantBool*>(const1)->getRawValue() == dynamic_cast<IRConstantBool*>(const2)->getRawValue(); }
        case IRInstruction::BinaryOps::SetNE:
            if(tyID == IRType::IntTyID){ return dynamic_cast<IRConstantInt*>(const1)->getRawValue() != dynamic_cast<IRConstantInt*>(const2)->getRawValue(); }
            else if(tyID == IRType::FloatTyID){ return dynamic_cast<IRConstantFloat*>(const1)->getRawValue() != dynamic_cast<IRConstantFloat*>(const2)->getRawValue(); }
            else if(tyID == IRType::DoubleTyID){ return dynamic_cast<IRConstantDouble*>(const1)->getRawValue() != dynamic_cast<IRConstantDouble*>(const2)->getRawValue(); }
            else if(tyID == IRType::BoolTyID){ return dynamic_cast<IRConstantBool*>(const1)->getRawValue() != dynamic_cast<IRConstantBool*>(const2)->getRawValue(); }
        case IRInstruction::BinaryOps::SetLE:
            if(tyID == IRType::IntTyID){ return dynamic_cast<IRConstantInt*>(const1)->getRawValue() <= dynamic_cast<IRConstantInt*>(const2)->getRawValue(); }
            else if(tyID == IRType::FloatTyID){ return dynamic_cast<IRConstantFloat*>(const1)->getRawValue() <= dynamic_cast<IRConstantFloat*>(const2)->getRawValue(); }
            else if(tyID == IRType::DoubleTyID){ return dynamic_cast<IRConstantDouble*>(const1)->getRawValue() <= dynamic_cast<IRConstantDouble*>(const2)->getRawValue(); }
        case IRInstruction::BinaryOps::SetGE:
            if(tyID == IRType::IntTyID){ return dynamic_cast<IRConstantInt*>(const1)->getRawValue() >= dynamic_cast<IRConstantInt*>(const2)->getRawValue(); }
            else if(tyID == IRType::FloatTyID){ return dynamic_cast<IRConstantFloat*>(const1)->getRawValue() >= dynamic_cast<IRConstantFloat*>(const2)->getRawValue(); }
            else if(tyID == IRType::DoubleTyID){ return dynamic_cast<IRConstantDouble*>(const1)->getRawValue() >= dynamic_cast<IRConstantDouble*>(const2)->getRawValue(); }
        case IRInstruction::BinaryOps::SetLT:
            if(tyID == IRType::IntTyID){ return dynamic_cast<IRConstantInt*>(const1)->getRawValue() < dynamic_cast<IRConstantInt*>(const2)->getRawValue(); }
            else if(tyID == IRType::FloatTyID){ return dynamic_cast<IRConstantFloat*>(const1)->getRawValue() < dynamic_cast<IRConstantFloat*>(const2)->getRawValue(); }
            else if(tyID == IRType::DoubleTyID){ return dynamic_cast<IRConstantDouble*>(const1)->getRawValue() < dynamic_cast<IRConstantDouble*>(const2)->getRawValue(); }
        case IRInstruction::BinaryOps::SetGT:
            if(tyID == IRType::IntTyID){ return dynamic_cast<IRConstantInt*>(const1)->getRawValue() > dynamic_cast<IRConstantInt*>(const2)->getRawValue(); }
            else if(tyID == IRType::FloatTyID){ return dynamic_cast<IRConstantFloat*>(const1)->getRawValue() > dynamic_cast<IRConstantFloat*>(const2)->getRawValue(); }
            else if(tyID == IRType::DoubleTyID){ return dynamic_cast<IRConstantDouble*>(const1)->getRawValue() > dynamic_cast<IRConstantDouble*>(const2)->getRawValue(); }
    }
}

void ConstantPass::runOnBasicBlock(IRBasicBlock &BB) {
    for (std::vector<IRInstruction*>::iterator instIterator= BB.getInstList().begin(); instIterator != BB.getInstList().end();) {
        auto inst = *instIterator;
        bool flag = true;

        if( IRInstruction::BinaryOps::Add <= inst->getOpcode()  &&
            inst->getOpcode() <= IRInstruction::BinaryOps::SetGT  && 
            inst->getOperand(0)->getValueType() == IRInstruction::ConstantVal   &&
            inst->getOperand(1)->getValueType() == IRInstruction::ConstantVal){
                /*消除该条指令，并且用新得到的irnewconst代替所有的uses*/
                if(inst->getOpcode() <= IRInstruction::BinaryOps::Xor){
                    IRConstant* irnewconst;
                    if(inst->getOperand(0)->getType()->getPrimitiveID() == IRType::BoolTyID) {
                        irnewconst = judge(inst->getOpcode(),
                                        dynamic_cast<IRConstantBool*>(inst->getOperand(0)), 
                                        dynamic_cast<IRConstantBool*>(inst->getOperand(1)));
                    }else{
                        irnewconst = alge(inst->getOpcode(),
                                        dynamic_cast<IRConstant*>(inst->getOperand(0)), 
                                        dynamic_cast<IRConstant*>(inst->getOperand(1)));
                    }

                    inst->dropAllReferences();
                    instIterator = BB.getInstList().erase(instIterator);
                    inst->replaceAllUsesWith(irnewconst);

                    flag = false;
                }
                else{
                    bool ret = setge(inst->getOpcode(), dynamic_cast<IRConstant*>(inst->getOperand(0)), dynamic_cast<IRConstant*>(inst->getOperand(1)));

                    /*删除掉原先的br指令并获取所有的信息*/
                    instIterator = BB.getInstList().erase(instIterator);
                    auto oldBrInst = dynamic_cast<IRBranchInst*>(*instIterator);
                    auto trueBB = oldBrInst->getSuccessor(0);
                    auto falseBB = oldBrInst->getSuccessor(1);
                    oldBrInst->dropAllReferences();
                    instIterator = BB.getInstList().erase(instIterator);

                    /*插入新的br指令*/
                    IRBranchInst* newBrInst;
                    if(ret == true){ newBrInst = new IRBranchInst(trueBB, nullptr, nullptr, &BB); }
                    else{ newBrInst = new IRBranchInst(falseBB, nullptr, nullptr, &BB); }

                    flag = false;
                }
            }
        else if( inst->getOpcode() == IRInstruction::BinaryOps::Add){
            if( inst->getOperand(0)->getValueType() == IRInstruction::ConstantVal &&
                dynamic_cast<IRConstantInt*>(inst->getOperand(0)) != nullptr &&
                dynamic_cast<IRConstantInt*>(inst->getOperand(0))->getRawValue() == 0){
                    inst->replaceAllUsesWith(inst->getOperand(1));
                    inst->dropAllReferences();
                    instIterator = BB.getInstList().erase(instIterator);
                    flag = false;
                }
            else if(inst->getOperand(1)->getValueType() == IRInstruction::ConstantVal &&
                    dynamic_cast<IRConstantInt*>(inst->getOperand(1)) != nullptr &&
                    dynamic_cast<IRConstantInt*>(inst->getOperand(1))->getRawValue() == 0){
                    inst->replaceAllUsesWith(inst->getOperand(0));
                    inst->dropAllReferences();
                    instIterator = BB.getInstList().erase(instIterator);
                    flag = false;
                }
        }
        else if(inst->getOpcode() == IRInstruction::Br  && 
                dynamic_cast<IRBranchInst*>(inst)->isConditional() &&
                dynamic_cast<IRBranchInst*>(inst)->getCondition()->getValueType() == IRInstruction::ConstantVal){
                
                auto oldBrInst = dynamic_cast<IRBranchInst*>(inst);
                    
                 /*删除掉原先的br指令并获取所有的信息*/
                instIterator = std::find(BB.getInstList().begin(), BB.getInstList().end(), oldBrInst);
                auto trueBB = oldBrInst->getSuccessor(0);
                auto falseBB = oldBrInst->getSuccessor(1);
                bool brcond = dynamic_cast<IRConstantBool*>(oldBrInst->getCondition())->getRawValue();
                oldBrInst->dropAllReferences();
                instIterator = BB.getInstList().erase(instIterator);

                /*插入新的br指令*/
                IRBranchInst* newBrInst;
                if(brcond == true){ newBrInst = new IRBranchInst(trueBB, nullptr, nullptr, &BB); }
                else{ newBrInst = new IRBranchInst(falseBB, nullptr, nullptr, &BB); }

                flag = false;
        }

        if(flag){
            instIterator++;
        }
    }
}

ConstantPass::ConstantPass(std::string name, int level) : BasicBlockPass(std::move(name), level) {

}

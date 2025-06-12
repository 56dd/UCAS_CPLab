#include "LiveVariable.h"
#include "IR/IRType.h"
#include "RegisterNode.h"
#include "IR/IRBasicBlock.h"
#include "IR/IRConstant.h"
#include "IR/IRGlobalVariable.h"
#include "IR/IRInstruction.h"
#include "IR/IRValue.h"
#include "IR/iMemory.h"
#include "IR/iTerminators.h"
#include "IR/iOther.h"
#include <algorithm>
#include <ostream>
#include <vector>
#include <iomanip>

void LiveVariable::genLiveVariable(IRFunction *F) {
    
    /*先生成数据流的活跃变量，然后是块内的活跃变量*/
    LiveVariableBB::genLiveVariableBB(F);
};

void LiveVariableInst::print(std::ostream& OS, IRInstruction* inst){
    std::string INLiveString;
    std::string OUTLiveString;
    
    INLiveString = "INLive: ";
    for(auto irval: *const_cast<IRInstruction *>(inst)->getLive()->getINLive())
        INLiveString = INLiveString + "%" + irval->getName() + ", ";
    OS << std::setw(200) << std::setfill(' ') << INLiveString;

    OUTLiveString +=  "     OUTLive: ";
    for(auto irval: *const_cast<IRInstruction *>(inst)->getLive()->getOUTLive())
        OUTLiveString = OUTLiveString + "%" + irval->getName() + ", ";
    OS << std::setw(100) << std::setfill(' ') << OUTLiveString;

    OS.seekp(static_cast<std::streampos>(static_cast<std::streamoff>(OS.tellp()) - 300));
}

void LiveVariableBB::print(std::ostream& OS, IRBasicBlock* BB){
    std::string INLiveString;
    std::string OUTLiveString;

    INLiveString = "INLive: ";
    for(auto irval: *const_cast<IRBasicBlock *>(BB)->getLive()->getINLive())
        INLiveString = INLiveString + "%" + irval->getName() + ", ";
    OS << std::setw(200) << std::setfill(' ') << INLiveString;

    OUTLiveString +=  "     OUTLive: ";
    for(auto irval: *const_cast<IRBasicBlock *>(BB)->getLive()->getOUTLive())
        OUTLiveString = OUTLiveString + "%" + irval->getName() + ", ";
    OS << std::setw(100) << std::setfill(' ') << OUTLiveString;

    OS.seekp(static_cast<std::streampos>(static_cast<std::streamoff>(OS.tellp()) - 300));
}

void LiveVariableBB::genLiveVariableBB(IRFunction *F) {
    /*IN[BB]=O*/
    for(auto BB: F->getBasicBlockList()){
        BB->getLive()->getINLive()->clear();
    }

    bool flag=true;
    /*一直迭代到不动点*/
    while(flag){
        flag = false;
        for(auto BB:F->getBasicBlockList()){
            /*OUT[B] = U(S是B的一个后继)IN[S]*/
            for(auto succBB: BB->findSuccessor()){
                for(auto ir: *succBB->getLive()->getINLive()){
                    BB->getLive()->getOUTLive()->push_back(ir);
                }
            }

            /*对OUT进行去重处理*/
            auto OUTLive = BB->getLive()->getOUTLive();
            /*去重处理*/
            std::sort(OUTLive->begin(), OUTLive->end());
            OUTLive->erase(std::unique(OUTLive->begin(), OUTLive->end()), OUTLive->end());

            /*调用基本块内部的活跃变量分析得到基本块开头的Live变量*/
            LiveVariableInst::genLiveVariableInst(BB);

            /*IN[B] = OUT[inst]*/
            auto newINLive = BB->getInstList()[0]->getLive()->getINLive();
            if(!std::equal(newINLive->begin(), newINLive->end(),  BB->getLive()->getINLive()->begin(),  BB->getLive()->getINLive()->end()))
                flag = true;
            *BB->getLive()->getINLive() = *newINLive;
        }
    }
};

void LiveVariableInst::genLiveVariableInst(IRBasicBlock *BB) {

    unsigned i;
    for(i=BB->getInstList().size();i > 0;i--){

        /*OUT[i-1] = IN[i]*/
        if(i == BB->getInstList().size())
            *BB->getInstList()[i-1]->getLive()->getOUTLive() = *BB->getLive()->getOUTLive();
        else
            *BB->getInstList()[i-1]->getLive()->getOUTLive() = *BB->getInstList()[i]->getLive()->getINLive();

        auto inst= BB->getInstList()[i-1];
        auto INLive  = inst->getLive()->getINLive();
        auto OUTLive = inst->getLive()->getOUTLive();

        /*use[i-1] def[i-1]*/
        std::vector<IRValue*> usevec;
        std::vector<IRValue*> defvec;

        if(inst->isBinaryOp()){ 
            if(!dynamic_cast<IRConstant*>(inst->getOperand(0)))
                usevec.push_back(inst->getOperand(0));
            if(!dynamic_cast<IRConstant*>(inst->getOperand(1)))
                usevec.push_back(inst->getOperand(1));
            defvec.push_back(inst);
        }else if(inst->getOpcode() == IRInstruction::Call){
            if(inst->getType()->getPrimitiveID() != IRType::VoidTyID)
                defvec.push_back(inst);
            for(unsigned i=1; i<inst->getNumOperands(); i++){
                if(!dynamic_cast<IRConstant*>(inst->getOperand(i)))
                    usevec.push_back(inst->getOperand(i));
            }
        }else if(inst->getOpcode() == IRInstruction::Load){
            if(inst->getOperand(0)->getValueType() == IRValue::InstructionVal){
                if(dynamic_cast<IRInstruction *>(inst->getOperand(0))->getOpcode() != IRInstruction::Alloca)
                    usevec.push_back(inst->getOperand(0));
            }
            defvec.push_back(inst);
        }else if(inst->getOpcode() == IRInstruction::Shl ||
                 inst->getOpcode() == IRInstruction::Shr ){
            usevec.push_back(inst->getOperand(0));
            defvec.push_back(inst);
        }else if(inst->getOpcode() == IRInstruction::Store){
            if(!dynamic_cast<IRConstant*>(inst->getOperand(0)))
                usevec.push_back(inst->getOperand(0));
            
            if(inst->getOperand(1)->getValueType() == IRValue::InstructionVal){
                if(dynamic_cast<IRInstruction *>(inst->getOperand(1))->getOpcode() != IRInstruction::Alloca)
                    usevec.push_back(inst->getOperand(1));
            }
        }else if(inst->getOpcode() == IRInstruction::PHI){
            for(unsigned i=0; i<inst->getNumOperands(); i+=2){
                if(!dynamic_cast<IRConstant*>(inst->getOperand(i)))
                    usevec.push_back(inst->getOperand(i));
            }
            defvec.push_back(inst);
        }else if(inst->getOpcode() == IRInstruction::Br &&
                 dynamic_cast<IRBranchInst*>(inst)->isConditional()){
            if(!dynamic_cast<IRConstant*>(dynamic_cast<IRBranchInst*>(inst)->getCondition()))
                usevec.push_back(dynamic_cast<IRBranchInst*>(inst)->getCondition());
        }else if(inst->getOpcode() == IRInstruction::Ret){
            if(inst->getNumOperands() != 0 && !dynamic_cast<IRConstant*>(inst->getOperand(0)))
                usevec.push_back(dynamic_cast<IRReturnInst*>(inst)->getOperand(0));
        }else if(inst->getOpcode() == IRInstruction::Move){
            /*源操作数与目的操作数均与这条move指令相关*/
            defvec.push_back(inst->getOperand(0));
            if(!dynamic_cast<IRConstant*>(inst->getOperand(1))){
                usevec.push_back(dynamic_cast<IRMoveInst*>(inst)->getOperand(1));
            }
        }

        /*OUT[i-1]*/
        for(auto ir: *OUTLive){
            INLive->push_back(ir);
        }
        /*IN[i-1] = use[i-1]+OUT[i-1]*/
        for(auto ir: usevec){
            auto irout = std::find(INLive->begin(),INLive->end(), ir);
            if(irout == INLive->end() || INLive->empty()){   //未找到元素，则加入
                INLive->push_back(ir);
            }
        }
        /*IN[i-1] = use[i-1]+OUT[i-1]-def[i-1]*/
        for(auto ir: defvec){
            auto irout = std::find(INLive->begin(), INLive->end(), ir);
            if(irout != INLive->end() && !INLive->empty()){   //找到元素
                INLive->erase(irout);
            }
        }

        /*去重处理*/
        std::sort(INLive->begin(), INLive->end());
        INLive->erase(std::unique(INLive->begin(), INLive->end()), INLive->end());
    }
};

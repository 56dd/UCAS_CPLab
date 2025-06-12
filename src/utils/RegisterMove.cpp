
#include "IR/IRArgument.h"
#include "IR/IRInstruction.h"
#include "IR/IRValue.h"
#include "IR/iOther.h"
#include "RegisterMove.h"

RegisterMove::RegisterMove(IRMoveInst* moveinst){
    if(moveinst->getSrc()->getValueType() == IRValue::InstructionVal)
        srcNode = dynamic_cast<IRInstruction*>(moveinst->getSrc())->getRegNode();
    else if(moveinst->getSrc()->getValueType() == IRValue::ArgumentVal)
        srcNode = dynamic_cast<IRArgument*>(moveinst->getSrc())->getRegNode();
    dstNode = dynamic_cast<IRInstruction*>(moveinst->getDest())->getRegNode();
}

RegisterMove::RegisterMove(IRArgument* funcarg, Register* reg){
    srcNode = funcarg->getRegNode();
    dstNode = reg->getRegNode();
}
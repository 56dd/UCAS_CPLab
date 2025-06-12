#include "AlgebraicPass.h"
#include "IR/IRConstant.h"
#include "IR/IRDerivedTypes.h"
#include "IR/IRInstruction.h"
#include "IR/IRValue.h"
#include "IR/InstrTypes.h"
#include "IR/iMemory.h"
#include "IR/iOther.h"
#include "IR/iTerminators.h"

#include <algorithm>
#include <bitset>
#include <cstddef>
#include <string>
#include <utility>

#define MULCYCLE 7

void div2shift(std::vector<IRInstruction *>::iterator &inst, IRBasicBlock &BB) {
    IRInstruction *irinst;
    IRInstruction *irnewinst;
    IRValue *irvalue;
    IRConstantInt *irconst;

    irinst = *inst;
    /*!
     * 根据传入的inst判断const和irvalue
     */
    if (dynamic_cast<IRConstantInt *>(irinst->getOperand(1))) {
        irconst = dynamic_cast<IRConstantInt *>(irinst->getOperand(1));
        irvalue = irinst->getOperand(0);
    } else {
        inst++;
        return;
    }

    int num = irconst->getRawValue();
    int index = 0;

    std::bitset<32> bits(num);
    if (bits.count() == 1) {//拍数比较小才进行转换
        /*移位inst*/
        while (num != 0) {
            num = num >> 1;
            index++;
        }
        irnewinst = new IRShiftInst(IRInstruction::Shr, irvalue, IRConstantInt::get(index - 1),
                                    std::to_string(BB.getParent()->getCount()));
        BB.getParent()->addCount();

        /*消除inst*/
        inst = BB.getInstList().erase(inst);
        /*插入inst*/
        inst = BB.getInstList().insert(inst, irnewinst);

        /*全部替代*/
        irinst->replaceAllUsesWith(irnewinst);
    } else {
        inst++;
    }
}

void mul2shift(std::vector<IRInstruction *>::iterator &inst, IRBasicBlock &BB) {
    IRInstruction *irinst;
    std::vector<IRInstruction *> irinstArray;
    IRValue *irvalue;
    IRConstantInt *irconst;

    irinst = *inst;
    /*!
     * 根据传入的inst判断const和irvalue
     */
    if (dynamic_cast<IRConstantInt *>(irinst->getOperand(0))) {
        irconst = dynamic_cast<IRConstantInt *>(irinst->getOperand(0));
        irvalue = irinst->getOperand(1);
    } else if (dynamic_cast<IRConstantInt *>(irinst->getOperand(1))) {
        irconst = dynamic_cast<IRConstantInt *>(irinst->getOperand(1));
        irvalue = irinst->getOperand(0);
    } else {
        inst++;
        return;
    }

    int num = irconst->getRawValue();
    int index = 0;

    /*移位inst*/
    while (num != 0) {
        if (num % 2 == 1) {
            irinstArray.push_back(
                    new IRShiftInst(IRInstruction::Shl, irvalue, IRConstantInt::get(index),
                                    std::to_string(BB.getParent()->getCount())));
            BB.getParent()->addCount();
        }
        num = num >> 1;
        index++;
    }

    /*add inst*/
    int initSize = irinstArray.size();
    IRValue *irinitinst;
    /*如果出现移位数为0的情况，那么可以选择直接用原来的IRinstruction*/
    if (dynamic_cast<IRConstantInt *>(irinstArray[0]->getOperand(1))->getRawValue() == 0) {
        irinitinst = irinstArray[0]->getOperand(0);
        //irinstArray.erase(irinstArray.begin());
    } else {
        irinitinst = irinstArray[0];
    }
    for (unsigned i = 1; i < initSize; i++) {
        irinstArray.push_back(
                IRBinaryOperator::create(IRInstruction::Add, irinitinst, irinstArray[i],
                                         std::to_string(BB.getParent()->getCount())));
        irinitinst = irinstArray.back();
        BB.getParent()->addCount();
    }

    if (irinstArray.size() < MULCYCLE) {//拍数比较小才进行转换
        /*消除inst*/
        inst = BB.getInstList().erase(inst);

        /*插入新加的指令*/
        for (auto irinst: irinstArray) {
            inst = BB.getInstList().insert(inst, irinst);
            inst++;
        }

        /*全部替代*/
        irinst->replaceAllUsesWith(irinstArray.back());
    } else {
        inst++;
    }
}

void AlgebraicPass::runOnBasicBlock(IRBasicBlock &BB) {
    for (std::vector<IRInstruction *>::iterator inst = BB.getInstList().begin(); inst != BB.getInstList().end();) {
        if (dynamic_cast<IRInstruction *>(*inst)->getOpcode() == IRInstruction::Mul) {
            mul2shift(inst, BB);
        } else if (dynamic_cast<IRInstruction *>(*inst)->getOpcode() == IRInstruction::Div) {
            div2shift(inst, BB);
        } else {
            inst++;
        }
    }
}

AlgebraicPass::AlgebraicPass(std::string name, int level) : BasicBlockPass(name, level) {

}

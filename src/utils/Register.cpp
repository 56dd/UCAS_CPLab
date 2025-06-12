#include "Register.h"
#include "IR/IRConstant.h"
#include "IR/IRType.h"
#include "IR/IRValue.h"
#include "RegisterNode.h"
#include "IR/IRFunction.h"
#include "IR/IRBasicBlock.h"
#include "IR/iOther.h"
#include "utils/ErrorHandler.h"
#include <cstddef>
#include <cstdlib>
#include <ostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <utility>

std::vector<Register *> RegisterFactory::GeneralRegList = {};
std::vector<Register *> RegisterFactory::FloatRegList = {};
std::vector<CallerSavedRegister *> CallerSavedRegister::CallerSavedvec = {};
std::vector<CalleeSavedRegister *> CalleeSavedRegister::CalleeSavedvec = {};
std::vector<ParamRegister *> ParamRegister::Paramvec = {};
std::vector<FloatCallerSavedRegister *> FloatCallerSavedRegister::FloatCallerSavedvec = {};
std::vector<FloatCalleeSavedRegister *> FloatCalleeSavedRegister::FloatCalleeSavedvec = {};
std::vector<FloatParamRegister *> FloatParamRegister::FloatParamvec = {};

CalleeSavedRegister *CalleeSavedRegister::sp = new CalleeSavedRegister("sp");
CallerSavedRegister *CallerSavedRegister::ra = new CallerSavedRegister("ra");
ZeroRegister *ZeroRegister::zero = new ZeroRegister("zero");

CallerSavedRegister::CallerSavedRegister(unsigned int num) {
    regNum = num;
    if (num <= 2) { regSeq = num + 5; }
    else { regSeq = num + 25; }
    regName = "t" + std::to_string(regNum);
    regty = CallerSaved;
    regNode = new RegisterNode(regName, this);
}

CalleeSavedRegister::CalleeSavedRegister(unsigned int num) {
    regNum = num;
    if (num <= 1) { regSeq = num + 8; }
    else { regSeq = num + 16; }
    regName = "s" + std::to_string(regNum);
    regty = CalleeSaved;
    regNode = new RegisterNode(regName, this);
}

ParamRegister::ParamRegister(unsigned int num) {
    regNum = num;
    regSeq = num + 10;
    regName = "a" + std::to_string(regNum);
    regty = Param;
    regNode = new RegisterNode(regName, this);
}

FloatCallerSavedRegister::FloatCallerSavedRegister(unsigned int num) {
    regNum = num;
    if (num <= 7) { regSeq = num; }
    else { regSeq = num + 20; }
    regName = "ft" + std::to_string(regNum);
    regty = FloatCallerSaved;
    regNode = new RegisterNode(regName, this);
}

FloatCalleeSavedRegister::FloatCalleeSavedRegister(unsigned int num) {
    regNum = num;
    if (num <= 1) { regSeq = num + 8; }
    else { regSeq = num + 16; }
    regName = "fs" + std::to_string(regNum);
    regty = FloatCalleeSaved;
    regNode = new RegisterNode(regName, this);
}

FloatParamRegister::FloatParamRegister(unsigned int num) {
    regNum = num;
    regSeq = num + 10;
    regName = "fa" + std::to_string(regNum);
    regty = FloatParam;
    regNode = new RegisterNode(regName, this);
}

CallerSavedRegister *CallerSavedRegister::Num2Reg(unsigned int num) {
    for (auto reg: getTregList()) {
        if (reg->regNum == num)
            return reg;
    }
}

CallerSavedRegister::CallerSavedRegister(std::string name) {
    regName = name;
    regty = CallerSaved;
}

CalleeSavedRegister *CalleeSavedRegister::Num2Reg(unsigned int num) {
    for (auto reg: getSregList()) {
        if (reg->regNum == num)
            return reg;
    }
}

CalleeSavedRegister::CalleeSavedRegister(std::string name) {
    regName = name;
    regty = CalleeSaved;
}

ParamRegister *ParamRegister::Num2Reg(unsigned int num) {
    for (auto reg: getAregList()) {
        if (reg->regNum == num)
            return reg;
    }
}

FloatCallerSavedRegister *FloatCallerSavedRegister::Num2Reg(unsigned int num) {
    for (auto reg: getFTregList()) {
        if (reg->regNum == num)
            return reg;
    }
}

FloatCalleeSavedRegister *FloatCalleeSavedRegister::Num2Reg(unsigned int num) {
    for (auto reg: getFSregList()) {
        if (reg->regNum == num)
            return reg;
    }
}

FloatParamRegister *FloatParamRegister::Num2Reg(unsigned int num) {
    for (auto reg: getFAregList()) {
        if (reg->regNum == num)
            return reg;
    }
}

void RegisterFactory::printInst(std::ostream &OS, IRInstruction &inst) {
    /*打印inst中需要保存的寄存器*/
    OS << "CalleeSaved: ";
    for (auto reg: inst.getCalleeSavedINLiveRegList())
        OS << reg->getRegName() << ", ";

    OS << "CallerSaved: ";
    for (auto reg: inst.getCallerSavedINLiveRegList())
        OS << reg->getRegName() << ", ";
    OS << std::endl;

    OS << "FreeFloatCaller: ";
    auto Freg = inst.getFreeFloatCallerSavedReg();
    OS << const_cast<Register*>(Freg)->getRegName() << ", ";
    OS << std::endl;

    OS << "FreeGenCaller: ";
    auto Greg = inst.getFreeGenCallerSavedReg();
    OS << const_cast<Register*>(Greg)->getRegName() << ", ";
    OS << std::endl;
}

void RegisterFactory::print(std::ostream &OS, IRFunction &F) {

    /*打印F中需要保存的寄存器*/
    OS << F.getName() << ":" << std::endl;
    OS << "CalleeSaved: ";
    for (auto reg: F.getCalleeSavedRegList())
        OS << reg->getRegName() << ", ";
    OS << std::endl;

    OS << "CallerSaved: ";
    for (auto reg: F.getCallerSavedRegList())
        OS << reg->getRegName() << ", ";
    OS << std::endl << std::endl;

    /*打印ConstRegMap*/
    for (auto ConstReg: F.getConstRegMap()) {
        ConstReg.first->print(OS);
        OS << ": " << ConstReg.second->getRegName() << ", ";
    }
    OS << std::endl;

    /*打印整型寄存器*/
    for (auto reg: getGRegList()) {
        OS << reg->getRegName() << ": ";
        for (auto arg: F.getArgumentList()) {
            if (arg->getReg() == reg) {
                OS << arg->getName() << ", ";
            }
        }
        for (auto BB: F.getBasicBlockList()) {
            for (auto inst: BB->getInstList()) {
                if (inst->getOpcode() == IRInstruction::Move) {
                    if (dynamic_cast<IRInstruction *>(dynamic_cast<IRMoveInst *>(inst)->getDest())->getReg() == reg) {
                        OS << dynamic_cast<IRMoveInst *>(inst)->getDest()->getName() << ", ";
                    }
                } else {
                    if (inst->getReg() == reg) {
                        OS << inst->getName() << ", ";
                    }
                }
            }
        }
        OS << std::endl;
    }

    /*打印浮点型寄存器*/
    for (auto reg: getFRegList()) {
        OS << reg->getRegName() << ": ";
        for (auto arg: F.getArgumentList()) {
            if (arg->getReg() == reg) {
                OS << arg->getName() << ", ";
            }
        }
        for (auto BB: F.getBasicBlockList()) {
            for (auto inst: BB->getInstList()) {
                if (inst->getOpcode() == IRInstruction::Move) {
                    if (dynamic_cast<IRInstruction *>(dynamic_cast<IRMoveInst *>(inst)->getDest())->getReg() == reg) {
                        OS << dynamic_cast<IRMoveInst *>(inst)->getDest()->getName() << ", ";
                    }
                } else {
                    if (inst->getReg() == reg) {
                        OS << inst->getName() << ", ";
                    }
                }
            }
        }
        OS << std::endl;
    }
}

void RegisterFactory::check(IRFunction &F) {
    Register *Livereg;
    Register *instreg;

    for (auto BB: F.getBasicBlockList()) {
        for (auto inst: BB->getInstList()) {
            if ((inst->isBinaryOp() ||
                 (inst->getOpcode() == IRInstruction::Call && inst->getType()->getPrimitiveID() != IRType::VoidTyID) ||
                 inst->getOpcode() == IRInstruction::Load ||
                 inst->getOpcode() == IRInstruction::Shl ||
                 inst->getOpcode() == IRInstruction::Shr)) {
                instreg = inst->getReg();

                /*针对每一条指令，比较其与OUTLive的冲突*/
                for (auto ir: *inst->getLive()->getOUTLive()) {
                    if (ir->getValueType() == IRValue::InstructionVal)
                        Livereg = dynamic_cast<IRInstruction *>(ir)->getReg();
                    else if (ir->getValueType() == IRValue::ArgumentVal)
                        Livereg = dynamic_cast<IRArgument *>(ir)->getReg();

                    if ((Livereg == instreg && ir != inst) || Livereg == nullptr || instreg == nullptr) {
                        ErrorHandler::printErrorMessage(
                                "Register check fail at Function:" + F.getName() + " BasicBlock:" + BB->getName() +
                                " Instruction:" +
                                inst->getName() + ", " +
                                "conflict Register is " + Livereg->getRegName() + " between " +
                                inst->getName() + " and " + ir->getName());
                        exit(1);
                    }
                }
            } else if (inst->getOpcode() == IRInstruction::Move) {
                instreg = dynamic_cast<IRInstruction *>(inst->getOperand(0))->getReg();

                for (auto ir: *inst->getLive()->getOUTLive()) {
                    if (ir->getValueType() == IRValue::InstructionVal)
                        Livereg = dynamic_cast<IRInstruction *>(ir)->getReg();
                    else if (ir->getValueType() == IRValue::ArgumentVal)
                        Livereg = dynamic_cast<IRArgument *>(ir)->getReg();

                    /*这里如果是move的use，可以冲突*/
                    if ((Livereg == instreg && ir != inst->getOperand(1) && ir != inst->getOperand(0)) ||
                        Livereg == nullptr || instreg == nullptr) {
                        ErrorHandler::printErrorMessage(
                                "Register check fail at Function:" + F.getName() + " BasicBlock:" + BB->getName() +
                                " Instruction:" +
                                inst->getOperand(0)->getName() + ", " +
                                "conflict Register is " + Livereg->getRegName() + " between " +
                                inst->getOperand(0)->getName() + " and " + ir->getName());
                        exit(1);
                    }
                }
            }
        }
    }
}

void RegisterFactory::initGReg() {
    CallerSavedRegister::initTreg();
    CalleeSavedRegister::initSreg();
    ParamRegister::initAreg();

    if (GeneralRegList.empty()) {
        GeneralRegList.reserve(CallerSavedRegister::getTregList().size() +
                               CalleeSavedRegister::getSregList().size() +
                               ParamRegister::getAregList().size());
        std::copy(CallerSavedRegister::getTregList().begin(), CallerSavedRegister::getTregList().end(),
                  std::back_inserter(GeneralRegList));
        std::copy(CalleeSavedRegister::getSregList().begin(), CalleeSavedRegister::getSregList().end(),
                  std::back_inserter(GeneralRegList));
        std::copy(ParamRegister::getAregList().begin(), ParamRegister::getAregList().end(),
                  std::back_inserter(GeneralRegList));
    }
}

void RegisterFactory::initFReg() {
    FloatCallerSavedRegister::initFTreg();
    FloatCalleeSavedRegister::initFSreg();
    FloatParamRegister::initFAreg();

    if (FloatRegList.empty()) {
        FloatRegList.reserve(FloatCallerSavedRegister::getFTregList().size() +
                             FloatCalleeSavedRegister::getFSregList().size() +
                             FloatParamRegister::getFAregList().size());
        std::copy(FloatCallerSavedRegister::getFTregList().begin(), FloatCallerSavedRegister::getFTregList().end(),
                  std::back_inserter(FloatRegList));
        std::copy(FloatCalleeSavedRegister::getFSregList().begin(), FloatCalleeSavedRegister::getFSregList().end(),
                  std::back_inserter(FloatRegList));
        std::copy(FloatParamRegister::getFAregList().begin(), FloatParamRegister::getFAregList().end(),
                  std::back_inserter(FloatRegList));
    }

}

ZeroRegister::ZeroRegister(std::string name) {
    regName = std::move(name);
}

#include "IRBasicBlock.h"

#include "IRConstant.h"
#include "IRType.h"
#include "iPHINdoe.h"
#include "iTerminators.h"
#include "IRUse.h"
#include "IRUser.h"
#include <iostream>
#include <iomanip>

void IRBasicBlock::addInstruction(IRInstruction *inst) {
    if (!hasTerminator()) {
        InstList.push_back(inst);
    } else {
        inst->dropAllReferences();
    }
}

void IRBasicBlock::setParent(IRFunction *parent) {
    this->parent = parent;
}

IRBasicBlock::IRBasicBlock(const std::string &Name, IRFunction *Parent)
        : IRValue(IRType::LabelTy, IRValue::BasicBlockVal, Name) {
    Live = new LiveVariableBB(this);
    parent = Parent;
    if (Parent)
        parent->addBasicBlock(this);
}

IRBasicBlock::IRBasicBlock(const std::string &Name, IRBasicBlock *InsertBefore)
        : IRValue(IRType::LabelTy, IRValue::BasicBlockVal, Name) {
    Live = new LiveVariableBB(this);
    parent = InsertBefore->parent;
    InsertBefore->parent->addBasicBlock(this);
}

IRTerminatorInst *IRBasicBlock::getTerminator() {
    return dynamic_cast<IRTerminatorInst *>(InstList.back());
}

void IRBasicBlock::printPrefixName(std::ostream &OS) const {
    OS << "%" << this->getName();
}

void IRBasicBlock::print(std::ostream &OS) const {

    //LiveVariableBB::print(OS, const_cast<IRBasicBlock*>(this));

    //打印每条指令
    this->printPrefixName(OS);

    /******通过这个uses边去遍历它的user,查明是哪些块使用了它******/
    OS << ":                                               ; preds =";
    for (auto iruseptr: this->getUses()) {
        if (dynamic_cast<IRPHINode *>(iruseptr->getUser())) {
            continue;
        }
        OS << " ";//获得使用这个块的终止语句的父块
        dynamic_cast<IRTerminatorInst *>(iruseptr->getUser())->getParent()->printPrefixName(OS);
        OS << ",";//获得使用这个块的终止语句的父块
    }
    OS.seekp(static_cast<std::streampos>(static_cast<std::streamoff>(OS.tellp()) - 1));

    //OS << std::setw(80) << std::setfill(' ') << "INLive: ";

    OS.seekp(0, std::ios::end);
    OS << std::endl;

    for (auto inst: this->InstList) {
        inst->print(OS);
    }
    // TODO
}

bool IRBasicBlock::hasTerminator() {
    if (!InstList.empty() && getTerminator()) {
        return true;
    }
    return false;
}

void IRBasicBlock::addInstructionToFront(IRInstruction *inst) {
    inst->setParent(this);
    InstList.insert(InstList.begin(), inst);
}

std::vector<IRBasicBlock *> IRBasicBlock::findPredecessor() {
    std::vector<IRBasicBlock *> predecessor;
    for (auto use : this->getUses()) {
        auto brInst = dynamic_cast<IRBranchInst *>(use->getUser());
        if (brInst) {
            predecessor.push_back(brInst->getParent());
        }
    }
    return predecessor;
}

std::vector<IRBasicBlock *> IRBasicBlock::findSuccessor() {
   std::vector<IRBasicBlock *> successor;
   auto terminator = this->getTerminator();
   for (unsigned i = 0, E = terminator->getNumSuccessors(); i < E; ++i) {
       successor.push_back(terminator->getSuccessor(i));
   }
   return successor;
}

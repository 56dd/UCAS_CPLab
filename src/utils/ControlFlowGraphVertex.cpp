#include <cassert>
#include "ControlFlowGraphVertex.h"
#include <algorithm>
#include <iostream>
#include "IR/IRBasicBlock.h"

const std::vector<ControlFlowGraphVertex *> &ControlFlowGraphVertex::getSuccessors() const {
    return successors;
}

ControlFlowGraphVertex::ControlFlowGraphVertex(ControlFlowGraph *P, IRBasicBlock *BB,
                                               ControlFlowGraphVertex::vertexType ty)
        : parent(P), basicBlock(BB), ty(ty), dominatorTreeNode(BB, this) {
}

void ControlFlowGraphVertex::addSuccessor(ControlFlowGraphVertex *succ) {
    assert(std::find(successors.begin(), successors.end(), succ) == successors.end()
           && "push same edge twice");
    successors.push_back(succ);
    succ->predecessors.push_back(this);
}

const std::vector<ControlFlowGraphVertex *> &ControlFlowGraphVertex::getPredecessors() const {
    return predecessors;
}

IRBasicBlock *ControlFlowGraphVertex::getBasicBlock() const {
    return basicBlock;
}

ControlFlowGraph *ControlFlowGraphVertex::getParent() const {
    return parent;
}

ControlFlowGraphVertex::vertexType ControlFlowGraphVertex::getTy() const {
    return ty;
}

DominatorTree *ControlFlowGraphVertex::getDominatorTreeNode() {
    return &dominatorTreeNode;
}

void ControlFlowGraphVertex::print() {
    if (ty == BB) {
        std::cout << basicBlock->getName();
    } else if (ty == R) {
        std::cout << "r";
    } else if (ty == EXIT) {
        std::cout << "exit";
    }
}

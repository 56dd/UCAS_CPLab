#ifndef COMPILER_CONTROLFLOWGRAPHVERTEX_H
#define COMPILER_CONTROLFLOWGRAPHVERTEX_H

#include <vector>
#include "DominatorTree.h"

class IRBasicBlock;

class ControlFlowGraph;

class DominatorTree;

class ControlFlowGraphVertex {
public:
    enum vertexType {
        BB,
        R,
        EXIT
    };

    ControlFlowGraphVertex(ControlFlowGraph *P, IRBasicBlock *BB, vertexType ty);

    ~ControlFlowGraphVertex() = default;

    void addSuccessor(ControlFlowGraphVertex *succ);

    const std::vector<ControlFlowGraphVertex *> &getSuccessors() const;

    const std::vector<ControlFlowGraphVertex *> &getPredecessors() const;

    IRBasicBlock *getBasicBlock() const;

    ControlFlowGraph *getParent() const;

    vertexType getTy() const;

    DominatorTree *getDominatorTreeNode();

    void print();

private:
    std::vector<ControlFlowGraphVertex *> successors;

    std::vector<ControlFlowGraphVertex *> predecessors;

    IRBasicBlock *basicBlock;

    ControlFlowGraph *parent;

    vertexType ty;

    DominatorTree dominatorTreeNode;
};


#endif //COMPILER_CONTROLFLOWGRAPHVERTEX_H

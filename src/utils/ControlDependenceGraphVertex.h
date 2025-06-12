#ifndef COMPILER_CONTROLDEPENDENCEGRAPHVERTEX_H
#define COMPILER_CONTROLDEPENDENCEGRAPHVERTEX_H

#include <vector>

class IRBasicBlock;

class ControlDependenceGraph;

class ControlDependenceGraphVertex {
public:
    enum vertexType {
        BB,
        R,
        EXIT
    };

    ControlDependenceGraphVertex(ControlDependenceGraph *P, IRBasicBlock *BB, vertexType ty);

    ~ControlDependenceGraphVertex() = default;

    void addSuccessor(ControlDependenceGraphVertex *succ);

    const std::vector<ControlDependenceGraphVertex *> &getSuccessors() const;

    const std::vector<ControlDependenceGraphVertex *> &getPredecessors() const;

    IRBasicBlock *getBasicBlock() const;

    void print();

private:
    std::vector<ControlDependenceGraphVertex *> successors;

    std::vector<ControlDependenceGraphVertex *> predecessors;

    IRBasicBlock *basicBlock;

    ControlDependenceGraph *parent;

    vertexType ty;
};


#endif //COMPILER_CONTROLDEPENDENCEGRAPHVERTEX_H

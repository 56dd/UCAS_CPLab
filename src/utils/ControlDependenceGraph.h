#ifndef COMPILER_CONTROLDEPENDENCEGRAPH_H
#define COMPILER_CONTROLDEPENDENCEGRAPH_H

#include <set>
#include <map>
#include "DominatorTree.h"
#include "ControlFlowGraph.h"

class IRFunction;

class IRBasicBlock;

class ControlDependenceGraphVertex;

class ReverseControlFlowGraph;

class ControlDependenceGraph {
public:
    explicit ControlDependenceGraph(IRFunction *F);

    ~ControlDependenceGraph() = default;

    ControlDependenceGraphVertex *getVertexFromBasicBlock(IRBasicBlock *BB);

    const ReverseControlFlowGraph &getRCfg() const;

    ControlDependenceGraphVertex *getR() const;

    ControlDependenceGraphVertex *getExit() const;

    void print();

private:
    std::set<ControlDependenceGraphVertex *> vertexSet;
    std::map<IRBasicBlock *, ControlDependenceGraphVertex *> vertexMap;
    ControlDependenceGraphVertex *r;
    ControlDependenceGraphVertex *exit;
    ReverseControlFlowGraph rCfg;

    ControlDependenceGraphVertex *DT2V(DominatorTree *DT);
};


#endif //COMPILER_CONTROLDEPENDENCEGRAPH_H

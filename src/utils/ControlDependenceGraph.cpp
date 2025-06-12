#include <iostream>
#include "ControlDependenceGraph.h"
#include "utils/ControlFlowGraph.h"
#include "utils/ControlFlowGraphVertex.h"
#include "utils/ControlDependenceGraphVertex.h"
#include "DominatorTree.h"
#include "IR/IRFunction.h"

ControlDependenceGraph::ControlDependenceGraph(IRFunction *F)
        : rCfg(F) {
    auto BBList = F->getBasicBlockList();
    for (auto BB: BBList) {
        auto v = new ControlDependenceGraphVertex(this, BB, ControlDependenceGraphVertex::BB);
        vertexSet.insert(v);
        vertexMap[BB] = v;
    }
    r = new ControlDependenceGraphVertex(this, nullptr, ControlDependenceGraphVertex::R);
    exit = new ControlDependenceGraphVertex(this, nullptr, ControlDependenceGraphVertex::EXIT);
    vertexSet.insert(r);
    vertexSet.insert(exit);

    DominatorTree::getDominatorTree(&rCfg);

    for (auto vertex: rCfg.getVertexSet()) {
        auto chDT = vertex->getDominatorTreeNode();
        for (auto faDT: chDT->DF) {
            ControlDependenceGraphVertex *fa = DT2V(faDT);
            ControlDependenceGraphVertex *ch = DT2V(chDT);
            fa->addSuccessor(ch);
        }
    }
}

ControlDependenceGraphVertex *ControlDependenceGraph::DT2V(DominatorTree *DT) {
    if (DT->basicBlock)
        return vertexMap[DT->basicBlock];
    if (DT->vertex->getTy() == ControlFlowGraphVertex::EXIT)
        return exit;
    if (DT->vertex->getTy() == ControlFlowGraphVertex::R)
        return r;
    assert(0 && "wtf?");
    return nullptr;
}

ControlDependenceGraphVertex *ControlDependenceGraph::getVertexFromBasicBlock(IRBasicBlock *BB) {
    return vertexMap[BB];
}

const ReverseControlFlowGraph &ControlDependenceGraph::getRCfg() const {
    return rCfg;
}

ControlDependenceGraphVertex *ControlDependenceGraph::getR() const {
    return r;
}

ControlDependenceGraphVertex *ControlDependenceGraph::getExit() const {
    return exit;
}

void ControlDependenceGraph::print() {
    for (auto vertex: vertexSet) {
        for (auto succ: vertex->getSuccessors()) {
            vertex->print();
            std::cout << " ";
            succ->print();
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

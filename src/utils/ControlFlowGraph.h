#ifndef COMPILER_CONTROLFLOWGRAPH_H
#define COMPILER_CONTROLFLOWGRAPH_H

#include <vector>
#include <set>
#include <map>

class IRBasicBlock;

class IRFunction;

class ControlFlowGraphVertex;

class ControlFlowGraph {
public:
    explicit ControlFlowGraph(IRFunction *F);

    ControlFlowGraph() = default;

    virtual ~ControlFlowGraph() = default;

    ControlFlowGraphVertex *getEntry() const;

    const std::set<ControlFlowGraphVertex *> &getVertexSet() const;

    ControlFlowGraphVertex *getVertexFromBasicBlock(IRBasicBlock *BB);

    void print();

protected:
    std::set<ControlFlowGraphVertex *> vertexSet;
    std::map<IRBasicBlock *, ControlFlowGraphVertex *> vertexMap;
    ControlFlowGraphVertex *entry = nullptr;
};

class ReverseControlFlowGraph : public ControlFlowGraph {
private:
    ControlFlowGraphVertex *r;
    ControlFlowGraphVertex *exit;

public:
    explicit ReverseControlFlowGraph(IRFunction *F);

    ~ReverseControlFlowGraph() override = default;

    ControlFlowGraphVertex *getR() const;

    ControlFlowGraphVertex *getExit() const;
};


#endif //COMPILER_CONTROLFLOWGRAPH_H

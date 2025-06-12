#ifndef COMPILER_IRBASICBLOCK_H
#define COMPILER_IRBASICBLOCK_H
#pragma once

#include "IRFunction.h"
#include "IRInstruction.h"
#include "IRValue.h"
#include "utils/DominatorTree.h"
#include "utils/LiveVariable.h"
#include "utils/ControlFlowGraph.h"
#include "utils/ControlFlowGraphVertex.h"

class IRTerminatorInst;

class DominatorTree;

class LiveVariableBB;

class IRBasicBlock : public IRValue {
private:
    std::vector<IRInstruction *> InstList;

    IRFunction *parent;

    LiveVariableBB *Live;

public:
    explicit IRBasicBlock(const std::string &Name = "", IRFunction *Parent = nullptr);

    IRBasicBlock(const std::string &Name, IRBasicBlock *InsertBefore);

    ~IRBasicBlock() override = default;

    void setParent(IRFunction *parent);

    IRFunction *getParent() { return parent; }

    /******IRBasicBlock获得指令列表******/
    bool hasTerminator();

    IRTerminatorInst *getTerminator();//获得终止指令
    std::vector<IRInstruction *> &getInstList() { return InstList; }

    /******IRBasicBlock的打印方法******/
    void printPrefixName(std::ostream &OS) const override;

    virtual void print(std::ostream &OS) const;

    /******向InstList中添加instruction******/
    void addInstruction(IRInstruction *inst);

    void addInstructionToFront(IRInstruction *inst);

    DominatorTree *getDominatorTree(ControlFlowGraph *G) { return getControlGraphVertex(G)->getDominatorTreeNode(); }

    ControlFlowGraphVertex *getControlGraphVertex(ControlFlowGraph *G) { return G->getVertexFromBasicBlock(this); }

    LiveVariableBB *getLive() { return Live; }

    std::vector<IRBasicBlock *> findPredecessor();

    std::vector<IRBasicBlock *> findSuccessor();

    /******classof方法，判断从父类下来的子类是不是对应的IRBasicBlock类******/
    static inline bool classof(const IRBasicBlock *BB) { return true; }

    static inline bool classof(const IRValue *V) {
        return V->getValueType() == IRValue::BasicBlockVal;
    }
};


#endif//COMPILER_IRBASICBLOCK_H

#include <iostream>
#include "ControlFlowGraph.h"
#include "IR/IRFunction.h"
#include "utils/ControlFlowGraphVertex.h"
#include "IR/iTerminators.h"

ControlFlowGraph::ControlFlowGraph(IRFunction *F) {
    auto &BBList = F->getBasicBlockList();

    std::vector<IRBasicBlock *> bin;
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto BB: BBList) {
            if (BB == F->getEntryBlock())
                continue;
            auto &instList = BB->getInstList();
            if (BB->getUses().empty() && std::find(bin.begin(), bin.end(), BB) == bin.end()) {
                for (auto inst: instList)
                    inst->dropAllReferences();
                instList.clear();
                bin.push_back(BB);
                changed = true;
            }
        }
    }

    for (auto trash: bin) {
        BBList.erase(std::find(BBList.begin(), BBList.end(), trash));
    }

    for (auto BB: BBList) {
        auto v = new ControlFlowGraphVertex(this, BB, ControlFlowGraphVertex::BB);
        vertexSet.insert(v);
        vertexMap[BB] = v;
    }

    for (auto BB: BBList) {
        auto terminator = BB->getTerminator();
        if (terminator == nullptr) {
            std::cerr << "Function " << F->getName() << " not full path return." << std::endl;
            throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                     std::to_string(__LINE__));
        }
        auto v = vertexMap[BB];
        for (unsigned idx = 0, E = terminator->getNumSuccessors(); idx < E; ++idx) {
            if (std::find(BBList.begin(), BBList.end(), terminator->getSuccessor(idx)) == BBList.end()) {
                std::cerr << "Function " << F->getName() << " not full path return." << std::endl;
                throw std::runtime_error("Semantic analysis failed at " + std::string(__FILE__) + ":" +
                                         std::to_string(__LINE__));
            }
            v->addSuccessor(vertexMap[terminator->getSuccessor(idx)]);
        }
    }
    entry = vertexMap[F->getEntryBlock()];
}

ControlFlowGraphVertex *ControlFlowGraph::getEntry() const {
    return entry;
}

const std::set<ControlFlowGraphVertex *> &ControlFlowGraph::getVertexSet() const {
    return vertexSet;
}

ControlFlowGraphVertex *ControlFlowGraph::getVertexFromBasicBlock(IRBasicBlock *BB) {
    return vertexMap[BB];
}

void ControlFlowGraph::print() {
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

ReverseControlFlowGraph::ReverseControlFlowGraph(IRFunction *F) : ControlFlowGraph() {
    auto BBList = F->getBasicBlockList();
    r = new ControlFlowGraphVertex(this, nullptr, ControlFlowGraphVertex::R);
    exit = new ControlFlowGraphVertex(this, nullptr, ControlFlowGraphVertex::EXIT);
    vertexSet.insert(r);
    vertexSet.insert(exit);
    for (auto BB: BBList) {
        auto v = new ControlFlowGraphVertex(this, BB, ControlFlowGraphVertex::BB);
        vertexSet.insert(v);
        vertexMap[BB] = v;
    }

    for (auto BB: BBList) {
        auto terminator = BB->getTerminator();
        auto v = vertexMap[BB];
        unsigned E = terminator->getNumSuccessors();
        if (E == 0) {
            exit->addSuccessor(vertexMap[BB]);
        } else {
            for (unsigned idx = 0; idx < E; ++idx) {
                vertexMap[terminator->getSuccessor(idx)]->addSuccessor(v);
            }
        }
    }

    vertexMap[F->getEntryBlock()]->addSuccessor(r);
    exit->addSuccessor(r);

    entry = exit;
}

ControlFlowGraphVertex *ReverseControlFlowGraph::getR() const {
    return r;
}

ControlFlowGraphVertex *ReverseControlFlowGraph::getExit() const {
    return exit;
}

#ifndef COMPILER_REACHINGDEFINITION_H
#define COMPILER_REACHINGDEFINITION_H

#include <set>
#include <map>

class IRStoreInst;

class IRGlobalVariable;

class ControlFlowGraphVertex;

class IRInstruction;

class ReachingDefinition {
private:
    static std::map<ControlFlowGraphVertex *, bool> visited;

    static void bruteForce(IRGlobalVariable *GV, ControlFlowGraphVertex *node, std::set<IRStoreInst *> *Set);

public:
    static std::set<IRStoreInst *> getReachingDefinitions(IRGlobalVariable *GV, IRInstruction *inst);
};


#endif //COMPILER_REACHINGDEFINITION_H

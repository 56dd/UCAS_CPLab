#ifndef COMPILER_OPTIMIZER_H
#define COMPILER_OPTIMIZER_H
#pragma once
#include <vector>
#include "Pass/Pass.h"

class Pass;

class Optimizer {
public:
    explicit Optimizer(IRModule *ir);
    void run();
    void addPass(Pass * pass);
    void build();
    void setLevel(int level);

private:
    std::vector<Pass *> passList;
    IRModule *ir;
    int level;
};


#endif //COMPILER_OPTIMIZER_H

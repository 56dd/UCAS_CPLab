#ifndef COMPILER_PASS_H
#define COMPILER_PASS_H
#pragma once
#include "IR/IRModule.h"
#include "Optimizer.h"

class Optimizer;

class Pass {
public:
    explicit Pass(std::string name, int level);

    virtual void run(IRModule &ir) = 0;

    void addToOpt(Optimizer &opt);

    int getLevel() const;

private:
    std::string name;

    int level = 0;
};

/*!
 * FunctionPass - 如果该Pass不删除或增加函数并且应用于所有函数的优化就继承此类
 */
class FunctionPass : public Pass {
public:
    explicit FunctionPass(std::string name, int level);

    /*!
     * runOnFunction - 在函数上运行的优化行为
     * @param F 函数引用
     */
    virtual void runOnFunction(IRFunction &F) = 0;

    /*!
     * run - 在IRModule上运行的优化行为
     * @param M IRModule引用
     */
    virtual void run(IRModule &M);
};

/*!
 * BasicBlockPass - 如果该Pass在一个basicBlock中做局部优化，不改变CFG
 */
class BasicBlockPass : public FunctionPass {
public:
    explicit BasicBlockPass(std::string name, int level);

    /*!
     * runOnBasicBlock - 在基本块上运行优化行为
     * @param BB IRBasicBlock引用
     */
    virtual void runOnBasicBlock(IRBasicBlock &BB) = 0;

    virtual void runOnFunction(IRFunction &F);
};

#endif //COMPILER_PASS_H

#ifndef COMPILER_PASS_H
#define COMPILER_PASS_H

#include <string>
#include <memory>
#include <chrono>

#include "IR/IRModule.h"

class Optimizer;

/**
 * @brief Base class for all optimization passes
 */
class Pass {
public:
    /**
     * @brief Constructs a Pass with name and optimization level
     * @param pass_name Name of the pass
     * @param optimization_level Optimization level this pass belongs to
     */
    explicit Pass(const std::string& pass_name, int optimization_level);

    /**
     * @brief Virtual destructor
     */
    virtual ~Pass() = default;

    /**
     * @brief Runs the pass on the given IR module
     * @param ir_module IR module to optimize
     * @throws std::runtime_error if pass execution fails
     */
    virtual void run(IRModule& ir_module) = 0;

    /**
     * @brief Adds this pass to the optimizer
     * @param optimizer Optimizer to add the pass to
     */
    void addToOptimizer(Optimizer& optimizer);

    /**
     * @brief Gets the optimization level of this pass
     * @return Optimization level
     */
    int getOptimizationLevel() const { return optimization_level_; }

    /**
     * @brief Gets the name of this pass
     * @return Pass name
     */
    const std::string& getName() const { return pass_name_; }

    /**
     * @brief Gets the execution time of the last run
     * @return Execution time in milliseconds
     */
    double getLastExecutionTime() const { return last_execution_time_; }

    /**
     * @brief Checks if the pass should be run at the given optimization level
     * @param level Current optimization level
     * @return True if pass should be run
     */
    bool shouldRunAtLevel(int level) const { return optimization_level_ <= level; }

protected:
    /**
     * @brief Records the execution time of the pass
     * @param start_time Start time
     * @param end_time End time
     */
    void recordExecutionTime(const std::chrono::high_resolution_clock::time_point& start_time,
                           const std::chrono::high_resolution_clock::time_point& end_time);

    /**
     * @brief Validates the pass state before execution
     * @throws std::runtime_error if validation fails
     */
    virtual void validateState() const;

private:
    std::string pass_name_;
    int optimization_level_;
    double last_execution_time_;
};

/**
 * @brief Pass that operates on individual functions
 * 
 * FunctionPass is designed for optimizations that:
 * - Do not delete or add functions
 * - Apply optimizations to all functions in the module
 * - May modify the control flow within functions
 */
class FunctionPass : public Pass {
public:
    /**
     * @brief Constructs a FunctionPass
     * @param pass_name Name of the pass
     * @param optimization_level Optimization level
     */
    explicit FunctionPass(const std::string& pass_name, int optimization_level);

    /**
     * @brief Destructor
     */
    ~FunctionPass() override = default;

    /**
     * @brief Runs the pass on the entire IR module
     * @param ir_module IR module to optimize
     */
    void run(IRModule& ir_module) override;

protected:
    /**
     * @brief Runs the pass on a single function
     * @param function Function to optimize
     * @throws std::runtime_error if function optimization fails
     */
    virtual void runOnFunction(IRFunction& function) = 0;

    /**
     * @brief Validates the function before optimization
     * @param function Function to validate
     * @throws std::runtime_error if validation fails
     */
    virtual void validateFunction(const IRFunction& function) const;
};

/**
 * @brief Pass that operates on individual basic blocks
 * 
 * BasicBlockPass is designed for optimizations that:
 * - Operate within a single basic block
 * - Do not change the control flow graph (CFG)
 * - Perform local optimizations
 */
class BasicBlockPass : public FunctionPass {
public:
    /**
     * @brief Constructs a BasicBlockPass
     * @param pass_name Name of the pass
     * @param optimization_level Optimization level
     */
    explicit BasicBlockPass(const std::string& pass_name, int optimization_level);

    /**
     * @brief Destructor
     */
    ~BasicBlockPass() override = default;

protected:
    /**
     * @brief Runs the pass on a single function
     * @param function Function to optimize
     */
    void runOnFunction(IRFunction& function) override;

    /**
     * @brief Runs the pass on a single basic block
     * @param basic_block Basic block to optimize
     * @throws std::runtime_error if basic block optimization fails
     */
    virtual void runOnBasicBlock(IRBasicBlock& basic_block) = 0;

    /**
     * @brief Validates the basic block before optimization
     * @param basic_block Basic block to validate
     * @throws std::runtime_error if validation fails
     */
    virtual void validateBasicBlock(const IRBasicBlock& basic_block) const;
};

#endif // COMPILER_PASS_H

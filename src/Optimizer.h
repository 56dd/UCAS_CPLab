#ifndef COMPILER_OPTIMIZER_H
#define COMPILER_OPTIMIZER_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

#include "Pass/Pass.h"

class Pass;
class IRModule;

/**
 * @brief Optimization levels for the compiler
 */
enum class OptimizationLevel {
    NONE = 0,       ///< No optimizations
    BASIC = 1,      ///< Basic optimizations
    STANDARD = 2,   ///< Standard optimizations
    AGGRESSIVE = 3  ///< Aggressive optimizations
};

/**
 * @brief Optimizer class responsible for managing and running optimization passes
 */
class Optimizer {
public:
    /**
     * @brief Constructs an Optimizer with IR module
     * @param ir_module Pointer to the IR module to optimize
     */
    explicit Optimizer(IRModule* ir_module);

    /**
     * @brief Destructor
     */
    ~Optimizer() = default;

    /**
     * @brief Runs all optimization passes
     * @throws std::runtime_error if optimization fails
     */
    void run();

    /**
     * @brief Adds an optimization pass to the pass list
     * @param pass Pointer to the pass to add
     */
    void addPass(std::unique_ptr<Pass> pass);

    /**
     * @brief Builds the default optimization pipeline based on current level
     */
    void build();

    /**
     * @brief Sets the optimization level
     * @param level Optimization level (0-3)
     */
    void setLevel(int level);

    /**
     * @brief Sets the optimization level using enum
     * @param level Optimization level
     */
    void setLevel(OptimizationLevel level);

    /**
     * @brief Gets the current optimization level
     * @return Current optimization level
     */
    OptimizationLevel getLevel() const { return optimization_level_; }

    /**
     * @brief Gets the number of passes in the pipeline
     * @return Number of passes
     */
    size_t getPassCount() const { return passes_.size(); }

    /**
     * @brief Clears all optimization passes
     */
    void clearPasses();

    /**
     * @brief Gets pass statistics
     * @return Map of pass names to execution times
     */
    const std::unordered_map<std::string, double>& getPassStatistics() const { 
        return pass_statistics_; 
    }

private:
    std::vector<std::unique_ptr<Pass>> passes_;
    IRModule* ir_module_;
    OptimizationLevel optimization_level_;
    std::unordered_map<std::string, double> pass_statistics_;

    /**
     * @brief Builds basic optimization pipeline
     */
    void buildBasicPipeline();

    /**
     * @brief Builds standard optimization pipeline
     */
    void buildStandardPipeline();

    /**
     * @brief Builds aggressive optimization pipeline
     */
    void buildAggressivePipeline();

    /**
     * @brief Validates the internal state
     * @throws std::runtime_error if validation fails
     */
    void validateState() const;

    /**
     * @brief Records pass execution statistics
     * @param pass_name Name of the pass
     * @param execution_time Execution time in seconds
     */
    void recordPassStatistics(const std::string& pass_name, double execution_time);
};

#endif // COMPILER_OPTIMIZER_H

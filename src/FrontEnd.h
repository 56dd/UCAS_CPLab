#ifndef COMPILER_FRONTEND_H
#define COMPILER_FRONTEND_H

#include <memory>
#include <fstream>
#include <string>

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTVisitor.h"
#include "IR/IRModule.h"
#include "IRGenerator.h"
#include "SemanticAnalyzer.h"
#include "symbolTable.h"
#include "tree/ParseTree.h"
#include "utils/ErrorHandler.h"

using namespace antlr4;

/**
 * @brief Frontend compiler component responsible for lexical analysis, 
 *        parsing, semantic analysis, and IR generation
 */
class FrontEnd {
public:
    /**
     * @brief Constructs a FrontEnd with input stream and IR module
     * @param input_stream Pointer to the input source file stream
     * @param ir_module Pointer to the IR module to populate
     */
    explicit FrontEnd(std::ifstream* input_stream, IRModule* ir_module);

    /**
     * @brief Destructor
     */
    ~FrontEnd() = default;

    /**
     * @brief Performs complete frontend analysis including lexical analysis,
     *        parsing, semantic analysis, and IR generation
     * @throws std::runtime_error if analysis fails
     */
    void analyze();

    /**
     * @brief Prints the generated IR code to standard output
     */
    void print();

    /**
     * @brief Gets the IR module
     * @return Pointer to the IR module
     */
    IRModule* getIRModule() const { return ir_module_; }

    /**
     * @brief Gets the semantic analyzer
     * @return Reference to the semantic analyzer
     */
    const SemanticAnalyzer& getSemanticAnalyzer() const { return semantic_analyzer_; }

private:
    // ANTLR4 components
    std::unique_ptr<ANTLRInputStream> input_stream_;
    std::unique_ptr<CACTLexer> lexer_;
    std::unique_ptr<CommonTokenStream> token_stream_;
    std::unique_ptr<CACTParser> parser_;
    std::unique_ptr<tree::ParseTree> parse_tree_;

    // Compiler components
    IRModule* ir_module_;
    GlobalBlock global_block_;
    SemanticAnalyzer semantic_analyzer_;
    IRGenerator ir_generator_;

    /**
     * @brief Performs lexical analysis
     * @throws std::runtime_error if lexical analysis fails
     */
    void performLexicalAnalysis();

    /**
     * @brief Performs syntactic analysis (parsing)
     * @throws std::runtime_error if parsing fails
     */
    void performSyntacticAnalysis();

    /**
     * @brief Performs semantic analysis
     * @throws std::runtime_error if semantic analysis fails
     */
    void performSemanticAnalysis();

    /**
     * @brief Generates IR code
     * @throws std::runtime_error if IR generation fails
     */
    void generateIR();

    /**
     * @brief Validates the internal state
     * @throws std::runtime_error if validation fails
     */
    void validateState() const;
};

#endif // COMPILER_FRONTEND_H

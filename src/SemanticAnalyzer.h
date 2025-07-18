#ifndef COMPILER_SEMANTICANALYZER_H
#define COMPILER_SEMANTICANALYZER_H

#include <memory>
#include <stack>
#include <string>
#include <unordered_map>

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTVisitor.h"
#include "IR/IRModule.h"
#include "symbolTable.h"
#include "tree/ParseTree.h"
#include "utils/ErrorHandler.h"

using namespace antlr4;

/**
 * @brief Semantic Analyzer responsible for type checking and semantic validation
 * 
 * This class implements the visitor pattern to traverse the AST and perform
 * semantic analysis including type checking, scope validation, and error detection.
 */
class SemanticAnalyzer : public CACTVisitor {
public:
    /**
     * @brief Constructs a SemanticAnalyzer
     * @param global_block Global symbol table block
     * @param ir_module IR module for type information
     * @param parse_tree Root of the parse tree
     */
    explicit SemanticAnalyzer(GlobalBlock* global_block, IRModule* ir_module, tree::ParseTree* parse_tree);

    /**
     * @brief Destructor
     */
    ~SemanticAnalyzer() override = default;

    /**
     * @brief Performs semantic analysis on the parse tree
     * @throws std::runtime_error if semantic analysis fails
     */
    void analyze();

    // Visitor methods for different AST nodes
    std::any visitFunctionType(CACTParser::FunctionTypeContext* context) override;
    std::any visitBasicType(CACTParser::BasicTypeContext* context) override;
    std::any visitPrimaryExpression(CACTParser::PrimaryExpressionContext* context) override;
    std::any visitUnaryExpression(CACTParser::UnaryExpressionContext* context) override;
    std::any visitFunctionRParams(CACTParser::FunctionRParamsContext* context) override;
    std::any visitUnaryOperator(CACTParser::UnaryOperatorContext* context) override;
    std::any visitMultiplicativeExpression(CACTParser::MultiplicativeExpressionContext* context) override;
    std::any visitAdditiveExpression(CACTParser::AdditiveExpressionContext* context) override;
    std::any visitRelationalExpression(CACTParser::RelationalExpressionContext* context) override;
    std::any visitEqualityExpression(CACTParser::EqualityExpressionContext* context) override;
    std::any visitLogicalAndExpression(CACTParser::LogicalAndExpressionContext* context) override;
    std::any visitLogicalOrExpression(CACTParser::LogicalOrExpressionContext* context) override;
    std::any visitExpression(CACTParser::ExpressionContext* context) override;
    std::any visitConstantExpression(CACTParser::ConstantExpressionContext* context) override;
    std::any visitCondition(CACTParser::ConditionContext* context) override;
    std::any visitDeclaration(CACTParser::DeclarationContext* context) override;
    std::any visitConstantDeclaration(CACTParser::ConstantDeclarationContext* context) override;
    std::any visitConstantDefinition(CACTParser::ConstantDefinitionContext* context) override;
    std::any visitConstantInitValue(CACTParser::ConstantInitValueContext* context) override;
    std::any visitVariableDeclaration(CACTParser::VariableDeclarationContext* context) override;
    std::any visitVariableDefinition(CACTParser::VariableDefinitionContext* context) override;
    std::any visitStatement(CACTParser::StatementContext* context) override;
    std::any visitCompoundStatement(CACTParser::CompoundStatementContext* context) override;
    std::any visitBlockItemList(CACTParser::BlockItemListContext* context) override;
    std::any visitBlockItem(CACTParser::BlockItemContext* context) override;
    std::any visitExpressionStatement(CACTParser::ExpressionStatementContext* context) override;
    std::any visitLValue(CACTParser::LValueContext* context) override;
    std::any visitSelectionStatement(CACTParser::SelectionStatementContext* context) override;
    std::any visitIterationStatement(CACTParser::IterationStatementContext* context) override;
    std::any visitJumpStatement(CACTParser::JumpStatementContext* context) override;
    std::any visitCompilationUnit(CACTParser::CompilationUnitContext* context) override;
    std::any visitTranslationUnit(CACTParser::TranslationUnitContext* context) override;
    std::any visitExternalDeclaration(CACTParser::ExternalDeclarationContext* context) override;
    std::any visitFunctionDefinition(CACTParser::FunctionDefinitionContext* context) override;
    std::any visitFunctionFParams(CACTParser::FunctionFParamsContext* context) override;
    std::any visitFunctionFParam(CACTParser::FunctionFParamContext* context) override;
    std::any visitIntegerConstant(CACTParser::IntegerConstantContext* context) override;
    std::any visitFloatingConstant(CACTParser::FloatingConstantContext* context) override;
    std::any visitMultiplicativeOp(CACTParser::MultiplicativeOpContext* context) override;
    std::any visitAdditiveOp(CACTParser::AdditiveOpContext* context) override;
    std::any visitRelationalOp(CACTParser::RelationalOpContext* context) override;
    std::any visitEqualityOp(CACTParser::EqualityOpContext* context) override;
    std::any visitLogicalAndOp(CACTParser::LogicalAndOpContext* context) override;
    std::any visitLogicalOrOp(CACTParser::LogicalOrOpContext* context) override;
    std::any visitAddOp(CACTParser::AddOpContext* context) override;

    /**
     * @brief Gets the current function being analyzed
     * @return Pointer to the current function symbol
     */
    FuncSymbolInfo* getCurrentFunction() const { return current_function_; }

    /**
     * @brief Gets the current block being analyzed
     * @return Pointer to the current block
     */
    BlockInfo* getCurrentBlock() const { return current_block_; }

    /**
     * @brief Gets the number of semantic errors found
     * @return Number of errors
     */
    size_t getErrorCount() const { return error_count_; }

    /**
     * @brief Gets the number of semantic warnings found
     * @return Number of warnings
     */
    size_t getWarningCount() const { return warning_count_; }

private:
    // Parse tree and symbol table
    tree::ParseTree* parse_tree_;
    GlobalBlock* global_block_;
    IRModule* ir_module_;

    // Current context during analysis
    BlockInfo* current_block_;
    FuncSymbolInfo* current_function_;
    ConstVarArraySymbolInfo* current_symbol_;

    // Context stacks for nested scopes
    std::stack<BlockInfo*> block_stack_;
    std::stack<FuncSymbolInfo*> function_stack_;
    std::stack<ConstVarArraySymbolInfo*> symbol_stack_;

    // Error tracking
    size_t error_count_;
    size_t warning_count_;

    // Helper methods for semantic analysis
    /**
     * @brief Pushes a new block context
     * @param block_info Block information
     */
    void pushBlockContext(BlockInfo* block_info);

    /**
     * @brief Pops the current block context
     */
    void popBlockContext();

    /**
     * @brief Pushes a new function context
     * @param function_symbol Function symbol information
     */
    void pushFunctionContext(FuncSymbolInfo* function_symbol);

    /**
     * @brief Pops the current function context
     */
    void popFunctionContext();

    /**
     * @brief Pushes a new symbol context
     * @param symbol_info Symbol information
     */
    void pushSymbolContext(ConstVarArraySymbolInfo* symbol_info);

    /**
     * @brief Pops the current symbol context
     */
    void popSymbolContext();

    /**
     * @brief Validates type compatibility
     * @param expected_type Expected type
     * @param actual_type Actual type
     * @param context Context for error reporting
     * @return True if types are compatible
     */
    bool validateTypeCompatibility(const std::string& expected_type, 
                                 const std::string& actual_type,
                                 const std::string& context);

    /**
     * @brief Validates variable declaration
     * @param var_name Variable name
     * @param var_type Variable type
     * @param context Context for error reporting
     * @return True if declaration is valid
     */
    bool validateVariableDeclaration(const std::string& var_name,
                                   const std::string& var_type,
                                   const std::string& context);

    /**
     * @brief Validates function call
     * @param func_name Function name
     * @param param_types Parameter types
     * @param context Context for error reporting
     * @return True if function call is valid
     */
    bool validateFunctionCall(const std::string& func_name,
                            const std::vector<std::string>& param_types,
                            const std::string& context);

    /**
     * @brief Validates the current state
     * @throws std::runtime_error if validation fails
     */
    void validateState() const;

    /**
     * @brief Reports a semantic error
     * @param message Error message
     * @param context Context information
     */
    void reportError(const std::string& message, const std::string& context = "");

    /**
     * @brief Reports a semantic warning
     * @param message Warning message
     * @param context Context information
     */
    void reportWarning(const std::string& message, const std::string& context = "");
};

#endif // COMPILER_SEMANTICANALYZER_H

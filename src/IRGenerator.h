#ifndef COMPILER_IRGENERATOR_H
#define COMPILER_IRGENERATOR_H

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

using namespace antlr4;

/**
 * @brief IR Generator responsible for translating AST to IR code
 * 
 * This class implements the visitor pattern to traverse the AST and
 * generate corresponding IR instructions.
 */
class IRGenerator : public CACTVisitor {
public:
    /**
     * @brief Constructs an IRGenerator
     * @param global_block Global symbol table block
     * @param ir_module IR module to populate
     * @param parse_tree Root of the parse tree
     */
    IRGenerator(GlobalBlock* global_block, IRModule* ir_module, tree::ParseTree* parse_tree);

    /**
     * @brief Destructor
     */
    ~IRGenerator() override = default;

    /**
     * @brief Generates IR code from the parse tree
     * @throws std::runtime_error if IR generation fails
     */
    void generate();

    // Visitor methods for different AST nodes
    std::any visitCompilationUnit(CACTParser::CompilationUnitContext* context) override;
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
    std::any visitTranslationUnit(CACTParser::TranslationUnitContext* context) override;
    std::any visitExternalDeclaration(CACTParser::ExternalDeclarationContext* context) override;
    std::any visitFunctionDefinition(CACTParser::FunctionDefinitionContext* context) override;
    std::any visitFunctionFParams(CACTParser::FunctionFParamsContext* context) override;
    std::any visitFunctionFParam(CACTParser::FunctionFParamContext* context) override;
    std::any visitIntegerConstant(CACTParser::IntegerConstantContext* context) override;
    std::any visitFloatingConstant(CACTParser::FloatingConstantContext* context) override;
    std::any visitAddOp(CACTParser::AddOpContext* context) override;
    std::any visitMultiplicativeOp(CACTParser::MultiplicativeOpContext* context) override;
    std::any visitAdditiveOp(CACTParser::AdditiveOpContext* context) override;
    std::any visitRelationalOp(CACTParser::RelationalOpContext* context) override;
    std::any visitEqualityOp(CACTParser::EqualityOpContext* context) override;
    std::any visitLogicalAndOp(CACTParser::LogicalAndOpContext* context) override;
    std::any visitLogicalOrOp(CACTParser::LogicalOrOpContext* context) override;

    /**
     * @brief Gets the current IR module
     * @return Pointer to the IR module
     */
    IRModule* getIRModule() const { return ir_module_; }

    /**
     * @brief Gets the current function being processed
     * @return Pointer to the current function
     */
    IRFunction* getCurrentFunction() const { return current_function_; }

    /**
     * @brief Gets the current basic block being processed
     * @return Pointer to the current basic block
     */
    IRBasicBlock* getCurrentBasicBlock() const { return current_basic_block_; }

private:
    // Parse tree and symbol table
    tree::ParseTree* parse_tree_;
    GlobalBlock* global_block_;
    IRModule* ir_module_;

    // Current context during IR generation
    BlockInfo* current_block_;
    FuncSymbolInfo* current_function_symbol_;
    IRFunction* current_function_;
    IRBasicBlock* current_basic_block_;

    // Context stacks for nested scopes
    std::stack<BlockInfo*> block_stack_;
    std::stack<FuncSymbolInfo*> function_stack_;
    std::stack<IRFunction*> ir_function_stack_;
    std::stack<IRBasicBlock*> basic_block_stack_;

    // Helper methods for IR generation
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
     * @param ir_function IR function
     */
    void pushFunctionContext(FuncSymbolInfo* function_symbol, IRFunction* ir_function);

    /**
     * @brief Pops the current function context
     */
    void popFunctionContext();

    /**
     * @brief Pushes a new basic block context
     * @param basic_block IR basic block
     */
    void pushBasicBlockContext(IRBasicBlock* basic_block);

    /**
     * @brief Pops the current basic block context
     */
    void popBasicBlockContext();

    /**
     * @brief Creates a new basic block
     * @param name Basic block name
     * @return Pointer to the new basic block
     */
    IRBasicBlock* createBasicBlock(const std::string& name);

    /**
     * @brief Validates the current state
     * @throws std::runtime_error if validation fails
     */
    void validateState() const;

    /**
     * @brief Generates IR for a binary operation
     * @param op_type Operation type
     * @param lhs Left hand side operand
     * @param rhs Right hand side operand
     * @return Generated IR value
     */
    IRValue* generateBinaryOperation(const std::string& op_type, IRValue* lhs, IRValue* rhs);

    /**
     * @brief Generates IR for a unary operation
     * @param op_type Operation type
     * @param operand Operand
     * @return Generated IR value
     */
    IRValue* generateUnaryOperation(const std::string& op_type, IRValue* operand);
};

#endif // COMPILER_IRGENERATOR_H

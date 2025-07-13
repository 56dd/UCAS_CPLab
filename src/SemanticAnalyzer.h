#ifndef COMPILER_SEMANTICANALYZER_H
#define COMPILER_SEMANTICANALYZER_H

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTVisitor.h"
#include "IR/IRModule.h"
#include "symbolTable.h"
#include "tree/ParseTree.h"
#include "utils/ErrorHandler.h"

using namespace antlr4;

class SemanticAnalyzer : public CACTVisitor {
public:
    explicit SemanticAnalyzer(GlobalBlock *globalBlock, IRModule *ir, tree::ParseTree *root);

    std::any visitFunctionType(CACTParser::FunctionTypeContext *context) override;

    std::any visitBasicType(CACTParser::BasicTypeContext *context) override;

    std::any visitPrimaryExpression(CACTParser::PrimaryExpressionContext *context) override;

    std::any visitUnaryExpression(CACTParser::UnaryExpressionContext *context) override;

    std::any visitFunctionRParams(CACTParser::FunctionRParamsContext *context) override;

    std::any visitUnaryOperator(CACTParser::UnaryOperatorContext *context) override;

    std::any visitMultiplicativeExpression(CACTParser::MultiplicativeExpressionContext *context) override;

    std::any visitAdditiveExpression(CACTParser::AdditiveExpressionContext *context) override;

    std::any visitRelationalExpression(CACTParser::RelationalExpressionContext *context) override;

    std::any visitEqualityExpression(CACTParser::EqualityExpressionContext *context) override;

    std::any visitLogicalAndExpression(CACTParser::LogicalAndExpressionContext *context) override;

    std::any visitLogicalOrExpression(CACTParser::LogicalOrExpressionContext *context) override;

    std::any visitExpression(CACTParser::ExpressionContext *context) override;

    std::any visitConstantExpression(CACTParser::ConstantExpressionContext *context) override;

    std::any visitCondition(CACTParser::ConditionContext *context) override;

    std::any visitDeclaration(CACTParser::DeclarationContext *context) override;

    std::any visitConstantDeclaration(CACTParser::ConstantDeclarationContext *context) override;

    std::any visitConstantDefinition(CACTParser::ConstantDefinitionContext *context) override;

    std::any visitConstantInitValue(CACTParser::ConstantInitValueContext *context) override;

    std::any visitVariableDeclaration(CACTParser::VariableDeclarationContext *context) override;

    std::any visitVariableDefinition(CACTParser::VariableDefinitionContext *context) override;

    std::any visitStatement(CACTParser::StatementContext *context) override;

    std::any visitCompoundStatement(CACTParser::CompoundStatementContext *context) override;

    std::any visitBlockItemList(CACTParser::BlockItemListContext *context) override;

    std::any visitBlockItem(CACTParser::BlockItemContext *context) override;

    std::any visitExpressionStatement(CACTParser::ExpressionStatementContext *context) override;

    std::any visitLValue(CACTParser::LValueContext *context) override;

    std::any visitSelectionStatement(CACTParser::SelectionStatementContext *context) override;

    std::any visitIterationStatement(CACTParser::IterationStatementContext *context) override;

    std::any visitJumpStatement(CACTParser::JumpStatementContext *context) override;

    std::any visitCompilationUnit(CACTParser::CompilationUnitContext *context) override;

    std::any visitTranslationUnit(CACTParser::TranslationUnitContext *context) override;

    std::any visitExternalDeclaration(CACTParser::ExternalDeclarationContext *context) override;

    std::any visitFunctionDefinition(CACTParser::FunctionDefinitionContext *context) override;

    std::any visitFunctionFParams(CACTParser::FunctionFParamsContext *context) override;

    std::any visitFunctionFParam(CACTParser::FunctionFParamContext *context) override;

    std::any visitIntegerConstant(CACTParser::IntegerConstantContext *context) override;

    std::any visitFloatingConstant(CACTParser::FloatingConstantContext *context) override;

    std::any visitMultiplicativeOp(CACTParser::MultiplicativeOpContext *context) override;

    std::any visitAdditiveOp(CACTParser::AdditiveOpContext *context) override;

    std::any visitRelationalOp(CACTParser::RelationalOpContext *context) override;

    std::any visitEqualityOp(CACTParser::EqualityOpContext *context) override;

    std::any visitLogicalAndOp(CACTParser::LogicalAndOpContext *context) override;

    std::any visitLogicalOrOp(CACTParser::LogicalOrOpContext *context) override;

    ~SemanticAnalyzer() override;

    void analyze();

    std::any visitAddOp(CACTParser::AddOpContext *context) override;

private:
    tree::ParseTree *root;
    GlobalBlock *globalBlock;
    BlockInfo *currentBlock;
    FuncSymbolInfo *currentFunc = nullptr;
    ConstVarArraySymbolInfo *currentSymbol;
    IRModule *ir;
};


#endif//COMPILER_SEMANTICANALYZER_H

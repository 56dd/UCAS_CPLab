
    #include <vector>
    #include <string>
    #include "utils/CACT.h"
    #include "symbolTable.h"
    #include "IR/IRBasicBlock.h"


// Generated from CACT.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CACTParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CACTParser.
 */
class  CACTVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CACTParser.
   */
    virtual std::any visitCompilationUnit(CACTParser::CompilationUnitContext *context) = 0;

    virtual std::any visitFunctionType(CACTParser::FunctionTypeContext *context) = 0;

    virtual std::any visitBasicType(CACTParser::BasicTypeContext *context) = 0;

    virtual std::any visitPrimaryExpression(CACTParser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitUnaryExpression(CACTParser::UnaryExpressionContext *context) = 0;

    virtual std::any visitFunctionRParams(CACTParser::FunctionRParamsContext *context) = 0;

    virtual std::any visitUnaryOperator(CACTParser::UnaryOperatorContext *context) = 0;

    virtual std::any visitAddOp(CACTParser::AddOpContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(CACTParser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeOp(CACTParser::MultiplicativeOpContext *context) = 0;

    virtual std::any visitAdditiveExpression(CACTParser::AdditiveExpressionContext *context) = 0;

    virtual std::any visitAdditiveOp(CACTParser::AdditiveOpContext *context) = 0;

    virtual std::any visitRelationalExpression(CACTParser::RelationalExpressionContext *context) = 0;

    virtual std::any visitRelationalOp(CACTParser::RelationalOpContext *context) = 0;

    virtual std::any visitEqualityExpression(CACTParser::EqualityExpressionContext *context) = 0;

    virtual std::any visitEqualityOp(CACTParser::EqualityOpContext *context) = 0;

    virtual std::any visitLogicalAndExpression(CACTParser::LogicalAndExpressionContext *context) = 0;

    virtual std::any visitLogicalAndOp(CACTParser::LogicalAndOpContext *context) = 0;

    virtual std::any visitLogicalOrExpression(CACTParser::LogicalOrExpressionContext *context) = 0;

    virtual std::any visitLogicalOrOp(CACTParser::LogicalOrOpContext *context) = 0;

    virtual std::any visitExpression(CACTParser::ExpressionContext *context) = 0;

    virtual std::any visitConstantExpression(CACTParser::ConstantExpressionContext *context) = 0;

    virtual std::any visitCondition(CACTParser::ConditionContext *context) = 0;

    virtual std::any visitDeclaration(CACTParser::DeclarationContext *context) = 0;

    virtual std::any visitConstantDeclaration(CACTParser::ConstantDeclarationContext *context) = 0;

    virtual std::any visitConstantDefinition(CACTParser::ConstantDefinitionContext *context) = 0;

    virtual std::any visitConstantInitValue(CACTParser::ConstantInitValueContext *context) = 0;

    virtual std::any visitVariableDeclaration(CACTParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitVariableDefinition(CACTParser::VariableDefinitionContext *context) = 0;

    virtual std::any visitStatement(CACTParser::StatementContext *context) = 0;

    virtual std::any visitCompoundStatement(CACTParser::CompoundStatementContext *context) = 0;

    virtual std::any visitBlockItemList(CACTParser::BlockItemListContext *context) = 0;

    virtual std::any visitBlockItem(CACTParser::BlockItemContext *context) = 0;

    virtual std::any visitExpressionStatement(CACTParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitLValue(CACTParser::LValueContext *context) = 0;

    virtual std::any visitSelectionStatement(CACTParser::SelectionStatementContext *context) = 0;

    virtual std::any visitIterationStatement(CACTParser::IterationStatementContext *context) = 0;

    virtual std::any visitJumpStatement(CACTParser::JumpStatementContext *context) = 0;

    virtual std::any visitTranslationUnit(CACTParser::TranslationUnitContext *context) = 0;

    virtual std::any visitExternalDeclaration(CACTParser::ExternalDeclarationContext *context) = 0;

    virtual std::any visitFunctionDefinition(CACTParser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitFunctionFParams(CACTParser::FunctionFParamsContext *context) = 0;

    virtual std::any visitFunctionFParam(CACTParser::FunctionFParamContext *context) = 0;

    virtual std::any visitIntegerConstant(CACTParser::IntegerConstantContext *context) = 0;

    virtual std::any visitFloatingConstant(CACTParser::FloatingConstantContext *context) = 0;


};


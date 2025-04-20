
    #include <vector>
    #include <string>


// Generated from CACT.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CACTVisitor.h"


/**
 * This class provides an empty implementation of CACTVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CACTBaseVisitor : public CACTVisitor {
public:

  virtual std::any visitFunctionType(CACTParser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicType(CACTParser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpression(CACTParser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpression(CACTParser::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOperator(CACTParser::UnaryOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionRParams(CACTParser::FunctionRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpression(CACTParser::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpression(CACTParser::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpression(CACTParser::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityExpression(CACTParser::EqualityExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExpression(CACTParser::LogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExpression(CACTParser::LogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(CACTParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantExpression(CACTParser::ConstantExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantInitValue(CACTParser::ConstantInitValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(CACTParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(CACTParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantDeclaration(CACTParser::ConstantDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstantDefinition(CACTParser::ConstantDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(CACTParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDefinition(CACTParser::VariableDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(CACTParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompoundStatement(CACTParser::CompoundStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(CACTParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSelectionStatement(CACTParser::SelectionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIterationStatement(CACTParser::IterationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJumpStatement(CACTParser::JumpStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItem(CACTParser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItemList(CACTParser::BlockItemListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLeftValue(CACTParser::LeftValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompilationUnit(CACTParser::CompilationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTranslationUnit(CACTParser::TranslationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExternalDeclaration(CACTParser::ExternalDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(CACTParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionFParams(CACTParser::FunctionFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionFParam(CACTParser::FunctionFParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(CACTParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }


};


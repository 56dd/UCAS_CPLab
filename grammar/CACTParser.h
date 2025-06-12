
    #include <vector>
    #include <string>
    #include "utils/CACT.h"
    #include "symbolTable.h"
    #include "IR/IRBasicBlock.h"


// Generated from CACT.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CACTParser : public antlr4::Parser {
public:
  enum {
    IntegerConstant = 1, FloatingConstant = 2, BooleanConstant = 3, Bool = 4, 
    Break = 5, Const = 6, Continue = 7, Double = 8, Else = 9, False = 10, 
    Float = 11, If = 12, Int = 13, Return = 14, True = 15, Void = 16, While = 17, 
    LeftParen = 18, RightParen = 19, LeftBracket = 20, RightBracket = 21, 
    LeftBrace = 22, RightBrace = 23, Less = 24, LessEqual = 25, Greater = 26, 
    GreaterEqual = 27, Plus = 28, Minus = 29, Star = 30, Div = 31, Mod = 32, 
    AndAnd = 33, OrOr = 34, Not = 35, Semi = 36, Comma = 37, Assign = 38, 
    Equal = 39, NotEqual = 40, Dot = 41, Identifier = 42, Whitespace = 43, 
    Newline = 44, BlockComment = 45, LineComment = 46
  };

  enum {
    RuleCompilationUnit = 0, RuleFunctionType = 1, RuleBasicType = 2, RulePrimaryExpression = 3, 
    RuleUnaryExpression = 4, RuleFunctionRParams = 5, RuleUnaryOperator = 6, 
    RuleAddOp = 7, RuleMultiplicativeExpression = 8, RuleMultiplicativeOp = 9, 
    RuleAdditiveExpression = 10, RuleAdditiveOp = 11, RuleRelationalExpression = 12, 
    RuleRelationalOp = 13, RuleEqualityExpression = 14, RuleEqualityOp = 15, 
    RuleLogicalAndExpression = 16, RuleLogicalAndOp = 17, RuleLogicalOrExpression = 18, 
    RuleLogicalOrOp = 19, RuleExpression = 20, RuleConstantExpression = 21, 
    RuleCondition = 22, RuleDeclaration = 23, RuleConstantDeclaration = 24, 
    RuleConstantDefinition = 25, RuleConstantInitValue = 26, RuleVariableDeclaration = 27, 
    RuleVariableDefinition = 28, RuleStatement = 29, RuleCompoundStatement = 30, 
    RuleBlockItemList = 31, RuleBlockItem = 32, RuleExpressionStatement = 33, 
    RuleLValue = 34, RuleSelectionStatement = 35, RuleIterationStatement = 36, 
    RuleJumpStatement = 37, RuleTranslationUnit = 38, RuleExternalDeclaration = 39, 
    RuleFunctionDefinition = 40, RuleFunctionFParams = 41, RuleFunctionFParam = 42, 
    RuleNumber = 43
  };

  explicit CACTParser(antlr4::TokenStream *input);

  CACTParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CACTParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CompilationUnitContext;
  class FunctionTypeContext;
  class BasicTypeContext;
  class PrimaryExpressionContext;
  class UnaryExpressionContext;
  class FunctionRParamsContext;
  class UnaryOperatorContext;
  class AddOpContext;
  class MultiplicativeExpressionContext;
  class MultiplicativeOpContext;
  class AdditiveExpressionContext;
  class AdditiveOpContext;
  class RelationalExpressionContext;
  class RelationalOpContext;
  class EqualityExpressionContext;
  class EqualityOpContext;
  class LogicalAndExpressionContext;
  class LogicalAndOpContext;
  class LogicalOrExpressionContext;
  class LogicalOrOpContext;
  class ExpressionContext;
  class ConstantExpressionContext;
  class ConditionContext;
  class DeclarationContext;
  class ConstantDeclarationContext;
  class ConstantDefinitionContext;
  class ConstantInitValueContext;
  class VariableDeclarationContext;
  class VariableDefinitionContext;
  class StatementContext;
  class CompoundStatementContext;
  class BlockItemListContext;
  class BlockItemContext;
  class ExpressionStatementContext;
  class LValueContext;
  class SelectionStatementContext;
  class IterationStatementContext;
  class JumpStatementContext;
  class TranslationUnitContext;
  class ExternalDeclarationContext;
  class FunctionDefinitionContext;
  class FunctionFParamsContext;
  class FunctionFParamContext;
  class NumberContext; 

  class  CompilationUnitContext : public antlr4::ParserRuleContext {
  public:
    CompilationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    TranslationUnitContext *translationUnit();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompilationUnitContext* compilationUnit();

  class  FunctionTypeContext : public antlr4::ParserRuleContext {
  public:
    FunctionTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Void();
    BasicTypeContext *basicType();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionTypeContext* functionType();

  class  BasicTypeContext : public antlr4::ParserRuleContext {
  public:
    BasicTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Int();
    antlr4::tree::TerminalNode *Bool();
    antlr4::tree::TerminalNode *Float();
    antlr4::tree::TerminalNode *Double();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BasicTypeContext* basicType();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LValueContext *lValue();
    NumberContext *number();
    antlr4::tree::TerminalNode *LeftParen();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RightParen();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExpressionContext *primaryExpression();
    UnaryOperatorContext *unaryOperator();
    UnaryExpressionContext *unaryExpression();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    FunctionRParamsContext *functionRParams();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryExpressionContext* unaryExpression();

  class  FunctionRParamsContext : public antlr4::ParserRuleContext {
  public:
    FuncSymbolInfo * func;
    FunctionRParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionRParamsContext* functionRParams();

  class  UnaryOperatorContext : public antlr4::ParserRuleContext {
  public:
    UnaryOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddOpContext *addOp();
    antlr4::tree::TerminalNode *Not();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryOperatorContext* unaryOperator();

  class  AddOpContext : public antlr4::ParserRuleContext {
  public:
    AddOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AddOpContext* addOp();

  class  MultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    MultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExpressionContext *> unaryExpression();
    UnaryExpressionContext* unaryExpression(size_t i);
    std::vector<MultiplicativeOpContext *> multiplicativeOp();
    MultiplicativeOpContext* multiplicativeOp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicativeExpressionContext* multiplicativeExpression();

  class  MultiplicativeOpContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Star();
    antlr4::tree::TerminalNode *Div();
    antlr4::tree::TerminalNode *Mod();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicativeOpContext* multiplicativeOp();

  class  AdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    AdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);
    std::vector<AdditiveOpContext *> additiveOp();
    AdditiveOpContext* additiveOp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdditiveExpressionContext* additiveExpression();

  class  AdditiveOpContext : public antlr4::ParserRuleContext {
  public:
    AdditiveOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdditiveOpContext* additiveOp();

  class  RelationalExpressionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    RelationalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AdditiveExpressionContext *> additiveExpression();
    AdditiveExpressionContext* additiveExpression(size_t i);
    RelationalOpContext *relationalOp();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelationalExpressionContext* relationalExpression();

  class  RelationalOpContext : public antlr4::ParserRuleContext {
  public:
    RelationalOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *LessEqual();
    antlr4::tree::TerminalNode *GreaterEqual();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelationalOpContext* relationalOp();

  class  EqualityExpressionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    EqualityExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RelationalExpressionContext *> relationalExpression();
    RelationalExpressionContext* relationalExpression(size_t i);
    EqualityOpContext *equalityOp();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqualityExpressionContext* equalityExpression();

  class  EqualityOpContext : public antlr4::ParserRuleContext {
  public:
    EqualityOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Equal();
    antlr4::tree::TerminalNode *NotEqual();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqualityOpContext* equalityOp();

  class  LogicalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    LogicalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EqualityExpressionContext *> equalityExpression();
    EqualityExpressionContext* equalityExpression(size_t i);
    std::vector<LogicalAndOpContext *> logicalAndOp();
    LogicalAndOpContext* logicalAndOp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalAndExpressionContext* logicalAndExpression();

  class  LogicalAndOpContext : public antlr4::ParserRuleContext {
  public:
    LogicalAndOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AndAnd();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalAndOpContext* logicalAndOp();

  class  LogicalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    LogicalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LogicalAndExpressionContext *> logicalAndExpression();
    LogicalAndExpressionContext* logicalAndExpression(size_t i);
    std::vector<LogicalOrOpContext *> logicalOrOp();
    LogicalOrOpContext* logicalOrOp(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalOrExpressionContext* logicalOrExpression();

  class  LogicalOrOpContext : public antlr4::ParserRuleContext {
  public:
    LogicalOrOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OrOr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalOrOpContext* logicalOrOp();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AdditiveExpressionContext *additiveExpression();
    antlr4::tree::TerminalNode *BooleanConstant();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  ConstantExpressionContext : public antlr4::ParserRuleContext {
  public:
    DataType dataType;
    ConstantExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberContext *number();
    AddOpContext *addOp();
    antlr4::tree::TerminalNode *BooleanConstant();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantExpressionContext* constantExpression();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    IRBasicBlock * trueBlock = nullptr;
    IRBasicBlock * falseBlock = nullptr;
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicalOrExpressionContext *logicalOrExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionContext* condition();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstantDeclarationContext *constantDeclaration();
    VariableDeclarationContext *variableDeclaration();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  ConstantDeclarationContext : public antlr4::ParserRuleContext {
  public:
    DataType dataType;
    ConstantDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    BasicTypeContext *basicType();
    std::vector<ConstantDefinitionContext *> constantDefinition();
    ConstantDefinitionContext* constantDefinition(size_t i);
    antlr4::tree::TerminalNode *Semi();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantDeclarationContext* constantDeclaration();

  class  ConstantDefinitionContext : public antlr4::ParserRuleContext {
  public:
    DataType dataType;
    std::vector<int> arraySize;
    ConstantDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Assign();
    ConstantInitValueContext *constantInitValue();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantDefinitionContext* constantDefinition();

  class  ConstantInitValueContext : public antlr4::ParserRuleContext {
  public:
    DataType dataType;
    std::vector<int> arraySize;
    int dimension;
    ConstantInitValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstantExpressionContext *constantExpression();
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    std::vector<ConstantInitValueContext *> constantInitValue();
    ConstantInitValueContext* constantInitValue(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantInitValueContext* constantInitValue();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    DataType dataType;
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BasicTypeContext *basicType();
    std::vector<VariableDefinitionContext *> variableDefinition();
    VariableDefinitionContext* variableDefinition(size_t i);
    antlr4::tree::TerminalNode *Semi();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  VariableDefinitionContext : public antlr4::ParserRuleContext {
  public:
    DataType dataType;
    std::vector<int> arraySize;
    VariableDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);
    antlr4::tree::TerminalNode *Assign();
    ConstantInitValueContext *constantInitValue();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDefinitionContext* variableDefinition();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CompoundStatementContext *compoundStatement();
    ExpressionStatementContext *expressionStatement();
    SelectionStatementContext *selectionStatement();
    IterationStatementContext *iterationStatement();
    JumpStatementContext *jumpStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  CompoundStatementContext : public antlr4::ParserRuleContext {
  public:
    BlockInfo * thisblockinfo;
    FuncSymbolInfo * thisfuncinfo = nullptr;
    CompoundStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    BlockItemListContext *blockItemList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompoundStatementContext* compoundStatement();

  class  BlockItemListContext : public antlr4::ParserRuleContext {
  public:
    BlockItemListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BlockItemContext *> blockItem();
    BlockItemContext* blockItem(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockItemListContext* blockItemList();

  class  BlockItemContext : public antlr4::ParserRuleContext {
  public:
    BlockItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    DeclarationContext *declaration();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockItemContext* blockItem();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    ExpressionContext *expression();
    LValueContext *lValue();
    antlr4::tree::TerminalNode *Assign();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  LValueContext : public antlr4::ParserRuleContext {
  public:
    bool loadable;
    LValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LValueContext* lValue();

  class  SelectionStatementContext : public antlr4::ParserRuleContext {
  public:
    BlockInfo * thisblockinfo;
    bool ifelseType = false;
    SelectionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *If();
    antlr4::tree::TerminalNode *LeftParen();
    ConditionContext *condition();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *Else();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SelectionStatementContext* selectionStatement();

  class  IterationStatementContext : public antlr4::ParserRuleContext {
  public:
    BlockInfo * thisblockinfo;
    IRBasicBlock * preheader = nullptr;
    IRBasicBlock * bodyBlock = nullptr;
    IRBasicBlock * latch = nullptr;
    IRBasicBlock * nextBlock = nullptr;
    IterationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *While();
    antlr4::tree::TerminalNode *LeftParen();
    ConditionContext *condition();
    antlr4::tree::TerminalNode *RightParen();
    StatementContext *statement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IterationStatementContext* iterationStatement();

  class  JumpStatementContext : public antlr4::ParserRuleContext {
  public:
    JumpStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Semi();
    antlr4::tree::TerminalNode *Continue();
    antlr4::tree::TerminalNode *Break();
    antlr4::tree::TerminalNode *Return();
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JumpStatementContext* jumpStatement();

  class  TranslationUnitContext : public antlr4::ParserRuleContext {
  public:
    TranslationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExternalDeclarationContext *> externalDeclaration();
    ExternalDeclarationContext* externalDeclaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TranslationUnitContext* translationUnit();

  class  ExternalDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ExternalDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDefinitionContext *functionDefinition();
    DeclarationContext *declaration();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExternalDeclarationContext* externalDeclaration();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    BlockInfo * thisblockinfo;
    FuncSymbolInfo * thisfuncinfo;
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionTypeContext *functionType();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    CompoundStatementContext *compoundStatement();
    FunctionFParamsContext *functionFParams();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  FunctionFParamsContext : public antlr4::ParserRuleContext {
  public:
    FuncSymbolInfo * thisfuncinfo;
    std::vector < SymbolInfo * > paramList;
    IRBasicBlock* irbasicblock;
    FunctionFParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FunctionFParamContext *> functionFParam();
    FunctionFParamContext* functionFParam(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionFParamsContext* functionFParams();

  class  FunctionFParamContext : public antlr4::ParserRuleContext {
  public:
    FuncSymbolInfo * thisfuncinfo;
    SymbolInfo * Fparam;
    unsigned beforeFuncCount;
    IRBasicBlock* irbasicblock;
    FunctionFParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BasicTypeContext *basicType();
    antlr4::tree::TerminalNode *Identifier();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode* LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode* RightBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IntegerConstant();
    antlr4::tree::TerminalNode* IntegerConstant(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionFParamContext* functionFParam();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    NumberContext() = default;
    void copyFrom(NumberContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FloatingConstantContext : public NumberContext {
  public:
    FloatingConstantContext(NumberContext *ctx);

    antlr4::tree::TerminalNode *FloatingConstant();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntegerConstantContext : public NumberContext {
  public:
    IntegerConstantContext(NumberContext *ctx);

    antlr4::tree::TerminalNode *IntegerConstant();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  NumberContext* number();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};


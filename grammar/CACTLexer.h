
    #include <vector>
    #include <string>
    #include "utils/CACT.h"
    #include "symbolTable.h"
    #include "IR/IRBasicBlock.h"


// Generated from CACT.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CACTLexer : public antlr4::Lexer {
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

  explicit CACTLexer(antlr4::CharStream *input);

  ~CACTLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};


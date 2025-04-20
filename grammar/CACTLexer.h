
    #include <vector>
    #include <string>


// Generated from CACT.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  CACTLexer : public antlr4::Lexer {
public:
  enum {
    Whitespace = 1, Newline = 2, CommentLine = 3, CommentBlock = 4, IntegerConstant = 5, 
    FloatingConstant = 6, CharacterConstant = 7, Const = 8, Continue = 9, 
    While = 10, Break = 11, True = 12, False = 13, If = 14, Else = 15, Void = 16, 
    Int = 17, Char = 18, Float = 19, Double = 20, Return = 21, LeftParenthesis = 22, 
    RightParenthesis = 23, LeftBracket = 24, RightBracket = 25, LeftBrace = 26, 
    RightBrace = 27, Less = 28, LessEqual = 29, Greater = 30, GreaterEqual = 31, 
    Plus = 32, Minus = 33, Star = 34, Div = 35, Mod = 36, AndAnd = 37, OrOr = 38, 
    Not = 39, Semicolon = 40, Comma = 41, Assign = 42, Equal = 43, NotEqual = 44, 
    Dot = 45, Identifier = 46
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


#ifndef COMPILER_ERRORHANDLER_H
#define COMPILER_ERRORHANDLER_H


#include "tree/ParseTree.h"

class SymbolInfo;

class ErrorHandler {
public:
    static void printErrorContext(antlr4::ParserRuleContext* context, const std::string& msg);
    static void printErrorSymbol(SymbolInfo* symbol, const std::string& msg);
    static void printErrorMessage(const std::string& msg);
};


#endif//COMPILER_ERRORHANDLER_H

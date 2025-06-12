#include "ErrorHandler.h"

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTVisitor.h"
#include "symbolTable.h"

void ErrorHandler::printErrorContext(antlr4::ParserRuleContext *context, const std::string &msg) {
    size_t line = context->start->getLine();
    size_t column = context->start->getCharPositionInLine();
    std::cerr << "Line " << std::to_string(line) << ":" << std::to_string(column) << " '" << context->getText() << "' "
              << msg << std::endl;
}

void ErrorHandler::printErrorSymbol(SymbolInfo *symbol, const std::string &msg) {
    int line = symbol->getline();
    std::string name = symbol->getName();
    std::cerr << "Line " << std::to_string(line) << " '" << name << "' " << msg << std::endl;
}

void ErrorHandler::printErrorMessage(const std::string &msg) {
    std::cerr << msg << std::endl;
}

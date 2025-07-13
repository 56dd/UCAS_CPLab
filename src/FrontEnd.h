#ifndef COMPILER_FRONTEND_H
#define COMPILER_FRONTEND_H

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTVisitor.h"
#include "IR/IRModule.h"
#include "IRGenerator.h"
#include "SemanticAnalyzer.h"
#include "symbolTable.h"
#include "tree/ParseTree.h"
#include "utils/ErrorHandler.h"

using namespace antlr4;

class FrontEnd {
public:
    explicit FrontEnd(std::ifstream *stream, IRModule *ir);

    void analyze();

    void print();

private:
    ANTLRInputStream input;
    CACTLexer lexer;
    CommonTokenStream tokens;
    CACTParser parser;
    tree::ParseTree *root;
    GlobalBlock globalBlock;
    IRModule *ir;
    SemanticAnalyzer analyzer;
    IRGenerator generator;
};


#endif//COMPILER_FRONTEND_H

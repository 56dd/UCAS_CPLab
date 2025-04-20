#include <iostream>
#include <ostream>
#include <type_traits>

// #include "antlr4-runtime.h"
#include "tree/ErrorNode.h"

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTVisitor.h"
#include "tree/ParseTree.h"

using namespace antlr4;

// class Analysis : public HelloVisitor {
// public:
//     std::any visitR(HelloParser::RContext *context) {
//         visitChildren( context );
        
//         std::cout << "enter rule [r]!" << std::endl;
//         std::cout << context->ID().data() << std::endl;
//         std::cout << "the ID is: " << context->ID(0)->getText() << std::endl;
//         std::cout << "the ID is: " << context->ID(1)->getText() << std::endl;
//         return nullptr;
//     }

//     std::any visitErrorNode(tree::ErrorNode * node) override {
//         std::cout << "visit error node!" << std::endl;
//         return nullptr;
//     }
// };

int main(int argc, const char* argv[]) {
  	if (argc < 2) {
   	 	std::cout << "Error! Missing source file" << std::endl;
		return 0;
	}
	std::ifstream stream;
	stream.open(argv[1]);

	ANTLRInputStream   input(stream);
	CACTLexer         lexer(&input);
	CommonTokenStream  tokens(&lexer);
	CACTParser        parser(&tokens);

	tree::ParseTree *ctx = parser.compilationUnit();

	int flag = 1;

	if (lexer.getNumberOfSyntaxErrors() > 0) {
		std::cout << "lex error: " << lexer.getNumberOfSyntaxErrors() << std::endl;
		flag = 0;
	}

	if (parser.getNumberOfSyntaxErrors() > 0) {
		std::cout << "syntax error: " << parser.getNumberOfSyntaxErrors() << std::endl;
		flag = 0;
	}

	if (flag)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	// std::cout << ctx->toStringTree() << std::endl;

	return 0;
}
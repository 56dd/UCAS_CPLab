
    #include <vector>
    #include <string>
    #include "utils/CACT.h"
    #include "symbolTable.h"
    #include "IR/IRBasicBlock.h"


// Generated from CACT.g4 by ANTLR 4.13.1


#include "CACTVisitor.h"

#include "CACTParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CACTParserStaticData final {
  CACTParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CACTParserStaticData(const CACTParserStaticData&) = delete;
  CACTParserStaticData(CACTParserStaticData&&) = delete;
  CACTParserStaticData& operator=(const CACTParserStaticData&) = delete;
  CACTParserStaticData& operator=(CACTParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag cactParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CACTParserStaticData *cactParserStaticData = nullptr;

void cactParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (cactParserStaticData != nullptr) {
    return;
  }
#else
  assert(cactParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CACTParserStaticData>(
    std::vector<std::string>{
      "compilationUnit", "functionType", "basicType", "primaryExpression", 
      "unaryExpression", "functionRParams", "unaryOperator", "addOp", "multiplicativeExpression", 
      "multiplicativeOp", "additiveExpression", "additiveOp", "relationalExpression", 
      "relationalOp", "equalityExpression", "equalityOp", "logicalAndExpression", 
      "logicalAndOp", "logicalOrExpression", "logicalOrOp", "expression", 
      "constantExpression", "condition", "declaration", "constantDeclaration", 
      "constantDefinition", "constantInitValue", "variableDeclaration", 
      "variableDefinition", "statement", "compoundStatement", "blockItemList", 
      "blockItem", "expressionStatement", "lValue", "selectionStatement", 
      "iterationStatement", "jumpStatement", "translationUnit", "externalDeclaration", 
      "functionDefinition", "functionFParams", "functionFParam", "number"
    },
    std::vector<std::string>{
      "", "", "", "", "'bool'", "'break'", "'const'", "'continue'", "'double'", 
      "'else'", "'false'", "'float'", "'if'", "'int'", "'return'", "'true'", 
      "'void'", "'while'", "'('", "')'", "'['", "']'", "'{'", "'}'", "'<'", 
      "'<='", "'>'", "'>='", "'+'", "'-'", "'*'", "'/'", "'%'", "'&&'", 
      "'||'", "'!'", "';'", "','", "'='", "'=='", "'!='", "'.'"
    },
    std::vector<std::string>{
      "", "IntegerConstant", "FloatingConstant", "BooleanConstant", "Bool", 
      "Break", "Const", "Continue", "Double", "Else", "False", "Float", 
      "If", "Int", "Return", "True", "Void", "While", "LeftParen", "RightParen", 
      "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "Less", 
      "LessEqual", "Greater", "GreaterEqual", "Plus", "Minus", "Star", "Div", 
      "Mod", "AndAnd", "OrOr", "Not", "Semi", "Comma", "Assign", "Equal", 
      "NotEqual", "Dot", "Identifier", "Whitespace", "Newline", "BlockComment", 
      "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,46,391,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,1,0,3,0,90,8,0,1,0,1,0,1,1,1,1,3,1,96,8,1,1,2,1,2,1,3,1,
  	3,1,3,1,3,1,3,1,3,3,3,106,8,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,115,8,4,
  	1,4,3,4,118,8,4,1,5,1,5,1,5,5,5,123,8,5,10,5,12,5,126,9,5,1,6,1,6,3,6,
  	130,8,6,1,7,1,7,1,8,1,8,1,8,1,8,5,8,138,8,8,10,8,12,8,141,9,8,1,9,1,9,
  	1,10,1,10,1,10,1,10,5,10,149,8,10,10,10,12,10,152,9,10,1,11,1,11,1,12,
  	1,12,1,12,1,12,3,12,160,8,12,1,13,1,13,1,14,1,14,1,14,1,14,3,14,168,8,
  	14,1,15,1,15,1,16,1,16,1,16,1,16,5,16,176,8,16,10,16,12,16,179,9,16,1,
  	17,1,17,1,18,1,18,1,18,1,18,5,18,187,8,18,10,18,12,18,190,9,18,1,19,1,
  	19,1,20,1,20,3,20,196,8,20,1,21,3,21,199,8,21,1,21,1,21,3,21,203,8,21,
  	1,22,1,22,1,23,1,23,3,23,209,8,23,1,24,1,24,1,24,1,24,1,24,5,24,216,8,
  	24,10,24,12,24,219,9,24,1,24,1,24,1,25,1,25,1,25,1,25,5,25,227,8,25,10,
  	25,12,25,230,9,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,5,26,240,8,
  	26,10,26,12,26,243,9,26,3,26,245,8,26,1,26,3,26,248,8,26,1,27,1,27,1,
  	27,1,27,5,27,254,8,27,10,27,12,27,257,9,27,1,27,1,27,1,28,1,28,1,28,1,
  	28,5,28,265,8,28,10,28,12,28,268,9,28,1,28,1,28,3,28,272,8,28,1,29,1,
  	29,1,29,1,29,1,29,3,29,279,8,29,1,30,1,30,3,30,283,8,30,1,30,1,30,1,31,
  	4,31,288,8,31,11,31,12,31,289,1,32,1,32,3,32,294,8,32,1,33,3,33,297,8,
  	33,1,33,1,33,1,33,1,33,1,33,1,33,3,33,305,8,33,1,34,1,34,1,34,1,34,1,
  	34,5,34,312,8,34,10,34,12,34,315,9,34,1,35,1,35,1,35,1,35,1,35,1,35,1,
  	35,3,35,324,8,35,1,36,1,36,1,36,1,36,1,36,1,36,1,37,1,37,1,37,1,37,3,
  	37,336,8,37,3,37,338,8,37,1,37,1,37,1,38,4,38,343,8,38,11,38,12,38,344,
  	1,39,1,39,3,39,349,8,39,1,40,1,40,1,40,1,40,3,40,355,8,40,1,40,1,40,1,
  	40,1,41,1,41,1,41,5,41,363,8,41,10,41,12,41,366,9,41,1,42,1,42,1,42,1,
  	42,3,42,372,8,42,1,42,1,42,1,42,3,42,377,8,42,1,42,5,42,380,8,42,10,42,
  	12,42,383,9,42,3,42,385,8,42,1,43,1,43,3,43,389,8,43,1,43,0,0,44,0,2,
  	4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,
  	52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,0,5,4,0,4,4,8,8,
  	11,11,13,13,1,0,28,29,1,0,30,32,1,0,24,27,1,0,39,40,396,0,89,1,0,0,0,
  	2,95,1,0,0,0,4,97,1,0,0,0,6,105,1,0,0,0,8,117,1,0,0,0,10,119,1,0,0,0,
  	12,129,1,0,0,0,14,131,1,0,0,0,16,133,1,0,0,0,18,142,1,0,0,0,20,144,1,
  	0,0,0,22,153,1,0,0,0,24,155,1,0,0,0,26,161,1,0,0,0,28,163,1,0,0,0,30,
  	169,1,0,0,0,32,171,1,0,0,0,34,180,1,0,0,0,36,182,1,0,0,0,38,191,1,0,0,
  	0,40,195,1,0,0,0,42,202,1,0,0,0,44,204,1,0,0,0,46,208,1,0,0,0,48,210,
  	1,0,0,0,50,222,1,0,0,0,52,247,1,0,0,0,54,249,1,0,0,0,56,260,1,0,0,0,58,
  	278,1,0,0,0,60,280,1,0,0,0,62,287,1,0,0,0,64,293,1,0,0,0,66,304,1,0,0,
  	0,68,306,1,0,0,0,70,316,1,0,0,0,72,325,1,0,0,0,74,337,1,0,0,0,76,342,
  	1,0,0,0,78,348,1,0,0,0,80,350,1,0,0,0,82,359,1,0,0,0,84,367,1,0,0,0,86,
  	388,1,0,0,0,88,90,3,76,38,0,89,88,1,0,0,0,89,90,1,0,0,0,90,91,1,0,0,0,
  	91,92,5,0,0,1,92,1,1,0,0,0,93,96,5,16,0,0,94,96,3,4,2,0,95,93,1,0,0,0,
  	95,94,1,0,0,0,96,3,1,0,0,0,97,98,7,0,0,0,98,5,1,0,0,0,99,106,3,68,34,
  	0,100,106,3,86,43,0,101,102,5,18,0,0,102,103,3,40,20,0,103,104,5,19,0,
  	0,104,106,1,0,0,0,105,99,1,0,0,0,105,100,1,0,0,0,105,101,1,0,0,0,106,
  	7,1,0,0,0,107,118,3,6,3,0,108,109,3,12,6,0,109,110,3,8,4,0,110,118,1,
  	0,0,0,111,112,5,42,0,0,112,114,5,18,0,0,113,115,3,10,5,0,114,113,1,0,
  	0,0,114,115,1,0,0,0,115,116,1,0,0,0,116,118,5,19,0,0,117,107,1,0,0,0,
  	117,108,1,0,0,0,117,111,1,0,0,0,118,9,1,0,0,0,119,124,3,40,20,0,120,121,
  	5,37,0,0,121,123,3,40,20,0,122,120,1,0,0,0,123,126,1,0,0,0,124,122,1,
  	0,0,0,124,125,1,0,0,0,125,11,1,0,0,0,126,124,1,0,0,0,127,130,3,14,7,0,
  	128,130,5,35,0,0,129,127,1,0,0,0,129,128,1,0,0,0,130,13,1,0,0,0,131,132,
  	7,1,0,0,132,15,1,0,0,0,133,139,3,8,4,0,134,135,3,18,9,0,135,136,3,8,4,
  	0,136,138,1,0,0,0,137,134,1,0,0,0,138,141,1,0,0,0,139,137,1,0,0,0,139,
  	140,1,0,0,0,140,17,1,0,0,0,141,139,1,0,0,0,142,143,7,2,0,0,143,19,1,0,
  	0,0,144,150,3,16,8,0,145,146,3,22,11,0,146,147,3,16,8,0,147,149,1,0,0,
  	0,148,145,1,0,0,0,149,152,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,
  	21,1,0,0,0,152,150,1,0,0,0,153,154,7,1,0,0,154,23,1,0,0,0,155,159,3,20,
  	10,0,156,157,3,26,13,0,157,158,3,20,10,0,158,160,1,0,0,0,159,156,1,0,
  	0,0,159,160,1,0,0,0,160,25,1,0,0,0,161,162,7,3,0,0,162,27,1,0,0,0,163,
  	167,3,24,12,0,164,165,3,30,15,0,165,166,3,24,12,0,166,168,1,0,0,0,167,
  	164,1,0,0,0,167,168,1,0,0,0,168,29,1,0,0,0,169,170,7,4,0,0,170,31,1,0,
  	0,0,171,177,3,28,14,0,172,173,3,34,17,0,173,174,3,28,14,0,174,176,1,0,
  	0,0,175,172,1,0,0,0,176,179,1,0,0,0,177,175,1,0,0,0,177,178,1,0,0,0,178,
  	33,1,0,0,0,179,177,1,0,0,0,180,181,5,33,0,0,181,35,1,0,0,0,182,188,3,
  	32,16,0,183,184,3,38,19,0,184,185,3,32,16,0,185,187,1,0,0,0,186,183,1,
  	0,0,0,187,190,1,0,0,0,188,186,1,0,0,0,188,189,1,0,0,0,189,37,1,0,0,0,
  	190,188,1,0,0,0,191,192,5,34,0,0,192,39,1,0,0,0,193,196,3,20,10,0,194,
  	196,5,3,0,0,195,193,1,0,0,0,195,194,1,0,0,0,196,41,1,0,0,0,197,199,3,
  	14,7,0,198,197,1,0,0,0,198,199,1,0,0,0,199,200,1,0,0,0,200,203,3,86,43,
  	0,201,203,5,3,0,0,202,198,1,0,0,0,202,201,1,0,0,0,203,43,1,0,0,0,204,
  	205,3,36,18,0,205,45,1,0,0,0,206,209,3,48,24,0,207,209,3,54,27,0,208,
  	206,1,0,0,0,208,207,1,0,0,0,209,47,1,0,0,0,210,211,5,6,0,0,211,212,3,
  	4,2,0,212,217,3,50,25,0,213,214,5,37,0,0,214,216,3,50,25,0,215,213,1,
  	0,0,0,216,219,1,0,0,0,217,215,1,0,0,0,217,218,1,0,0,0,218,220,1,0,0,0,
  	219,217,1,0,0,0,220,221,5,36,0,0,221,49,1,0,0,0,222,228,5,42,0,0,223,
  	224,5,20,0,0,224,225,5,1,0,0,225,227,5,21,0,0,226,223,1,0,0,0,227,230,
  	1,0,0,0,228,226,1,0,0,0,228,229,1,0,0,0,229,231,1,0,0,0,230,228,1,0,0,
  	0,231,232,5,38,0,0,232,233,3,52,26,0,233,51,1,0,0,0,234,248,3,42,21,0,
  	235,244,5,22,0,0,236,241,3,52,26,0,237,238,5,37,0,0,238,240,3,52,26,0,
  	239,237,1,0,0,0,240,243,1,0,0,0,241,239,1,0,0,0,241,242,1,0,0,0,242,245,
  	1,0,0,0,243,241,1,0,0,0,244,236,1,0,0,0,244,245,1,0,0,0,245,246,1,0,0,
  	0,246,248,5,23,0,0,247,234,1,0,0,0,247,235,1,0,0,0,248,53,1,0,0,0,249,
  	250,3,4,2,0,250,255,3,56,28,0,251,252,5,37,0,0,252,254,3,56,28,0,253,
  	251,1,0,0,0,254,257,1,0,0,0,255,253,1,0,0,0,255,256,1,0,0,0,256,258,1,
  	0,0,0,257,255,1,0,0,0,258,259,5,36,0,0,259,55,1,0,0,0,260,266,5,42,0,
  	0,261,262,5,20,0,0,262,263,5,1,0,0,263,265,5,21,0,0,264,261,1,0,0,0,265,
  	268,1,0,0,0,266,264,1,0,0,0,266,267,1,0,0,0,267,271,1,0,0,0,268,266,1,
  	0,0,0,269,270,5,38,0,0,270,272,3,52,26,0,271,269,1,0,0,0,271,272,1,0,
  	0,0,272,57,1,0,0,0,273,279,3,60,30,0,274,279,3,66,33,0,275,279,3,70,35,
  	0,276,279,3,72,36,0,277,279,3,74,37,0,278,273,1,0,0,0,278,274,1,0,0,0,
  	278,275,1,0,0,0,278,276,1,0,0,0,278,277,1,0,0,0,279,59,1,0,0,0,280,282,
  	5,22,0,0,281,283,3,62,31,0,282,281,1,0,0,0,282,283,1,0,0,0,283,284,1,
  	0,0,0,284,285,5,23,0,0,285,61,1,0,0,0,286,288,3,64,32,0,287,286,1,0,0,
  	0,288,289,1,0,0,0,289,287,1,0,0,0,289,290,1,0,0,0,290,63,1,0,0,0,291,
  	294,3,58,29,0,292,294,3,46,23,0,293,291,1,0,0,0,293,292,1,0,0,0,294,65,
  	1,0,0,0,295,297,3,40,20,0,296,295,1,0,0,0,296,297,1,0,0,0,297,298,1,0,
  	0,0,298,305,5,36,0,0,299,300,3,68,34,0,300,301,5,38,0,0,301,302,3,40,
  	20,0,302,303,5,36,0,0,303,305,1,0,0,0,304,296,1,0,0,0,304,299,1,0,0,0,
  	305,67,1,0,0,0,306,313,5,42,0,0,307,308,5,20,0,0,308,309,3,40,20,0,309,
  	310,5,21,0,0,310,312,1,0,0,0,311,307,1,0,0,0,312,315,1,0,0,0,313,311,
  	1,0,0,0,313,314,1,0,0,0,314,69,1,0,0,0,315,313,1,0,0,0,316,317,5,12,0,
  	0,317,318,5,18,0,0,318,319,3,44,22,0,319,320,5,19,0,0,320,323,3,58,29,
  	0,321,322,5,9,0,0,322,324,3,58,29,0,323,321,1,0,0,0,323,324,1,0,0,0,324,
  	71,1,0,0,0,325,326,5,17,0,0,326,327,5,18,0,0,327,328,3,44,22,0,328,329,
  	5,19,0,0,329,330,3,58,29,0,330,73,1,0,0,0,331,338,5,7,0,0,332,338,5,5,
  	0,0,333,335,5,14,0,0,334,336,3,40,20,0,335,334,1,0,0,0,335,336,1,0,0,
  	0,336,338,1,0,0,0,337,331,1,0,0,0,337,332,1,0,0,0,337,333,1,0,0,0,338,
  	339,1,0,0,0,339,340,5,36,0,0,340,75,1,0,0,0,341,343,3,78,39,0,342,341,
  	1,0,0,0,343,344,1,0,0,0,344,342,1,0,0,0,344,345,1,0,0,0,345,77,1,0,0,
  	0,346,349,3,80,40,0,347,349,3,46,23,0,348,346,1,0,0,0,348,347,1,0,0,0,
  	349,79,1,0,0,0,350,351,3,2,1,0,351,352,5,42,0,0,352,354,5,18,0,0,353,
  	355,3,82,41,0,354,353,1,0,0,0,354,355,1,0,0,0,355,356,1,0,0,0,356,357,
  	5,19,0,0,357,358,3,60,30,0,358,81,1,0,0,0,359,364,3,84,42,0,360,361,5,
  	37,0,0,361,363,3,84,42,0,362,360,1,0,0,0,363,366,1,0,0,0,364,362,1,0,
  	0,0,364,365,1,0,0,0,365,83,1,0,0,0,366,364,1,0,0,0,367,368,3,4,2,0,368,
  	384,5,42,0,0,369,371,5,20,0,0,370,372,5,1,0,0,371,370,1,0,0,0,371,372,
  	1,0,0,0,372,373,1,0,0,0,373,381,5,21,0,0,374,376,5,20,0,0,375,377,5,1,
  	0,0,376,375,1,0,0,0,376,377,1,0,0,0,377,378,1,0,0,0,378,380,5,21,0,0,
  	379,374,1,0,0,0,380,383,1,0,0,0,381,379,1,0,0,0,381,382,1,0,0,0,382,385,
  	1,0,0,0,383,381,1,0,0,0,384,369,1,0,0,0,384,385,1,0,0,0,385,85,1,0,0,
  	0,386,389,5,1,0,0,387,389,5,2,0,0,388,386,1,0,0,0,388,387,1,0,0,0,389,
  	87,1,0,0,0,44,89,95,105,114,117,124,129,139,150,159,167,177,188,195,198,
  	202,208,217,228,241,244,247,255,266,271,278,282,289,293,296,304,313,323,
  	335,337,344,348,354,364,371,376,381,384,388
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  cactParserStaticData = staticData.release();
}

}

CACTParser::CACTParser(TokenStream *input) : CACTParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CACTParser::CACTParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CACTParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *cactParserStaticData->atn, cactParserStaticData->decisionToDFA, cactParserStaticData->sharedContextCache, options);
}

CACTParser::~CACTParser() {
  delete _interpreter;
}

const atn::ATN& CACTParser::getATN() const {
  return *cactParserStaticData->atn;
}

std::string CACTParser::getGrammarFileName() const {
  return "CACT.g4";
}

const std::vector<std::string>& CACTParser::getRuleNames() const {
  return cactParserStaticData->ruleNames;
}

const dfa::Vocabulary& CACTParser::getVocabulary() const {
  return cactParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CACTParser::getSerializedATN() const {
  return cactParserStaticData->serializedATN;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

CACTParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::CompilationUnitContext::EOF() {
  return getToken(CACTParser::EOF, 0);
}

CACTParser::TranslationUnitContext* CACTParser::CompilationUnitContext::translationUnit() {
  return getRuleContext<CACTParser::TranslationUnitContext>(0);
}


size_t CACTParser::CompilationUnitContext::getRuleIndex() const {
  return CACTParser::RuleCompilationUnit;
}


std::any CACTParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::CompilationUnitContext* CACTParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, CACTParser::RuleCompilationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 76112) != 0)) {
      setState(88);
      translationUnit();
    }
    setState(91);
    match(CACTParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeContext ------------------------------------------------------------------

CACTParser::FunctionTypeContext::FunctionTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::FunctionTypeContext::Void() {
  return getToken(CACTParser::Void, 0);
}

CACTParser::BasicTypeContext* CACTParser::FunctionTypeContext::basicType() {
  return getRuleContext<CACTParser::BasicTypeContext>(0);
}


size_t CACTParser::FunctionTypeContext::getRuleIndex() const {
  return CACTParser::RuleFunctionType;
}


std::any CACTParser::FunctionTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFunctionType(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::FunctionTypeContext* CACTParser::functionType() {
  FunctionTypeContext *_localctx = _tracker.createInstance<FunctionTypeContext>(_ctx, getState());
  enterRule(_localctx, 2, CACTParser::RuleFunctionType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(95);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::Void: {
        enterOuterAlt(_localctx, 1);
        setState(93);
        match(CACTParser::Void);
        break;
      }

      case CACTParser::Bool:
      case CACTParser::Double:
      case CACTParser::Float:
      case CACTParser::Int: {
        enterOuterAlt(_localctx, 2);
        setState(94);
        basicType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicTypeContext ------------------------------------------------------------------

CACTParser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::BasicTypeContext::Int() {
  return getToken(CACTParser::Int, 0);
}

tree::TerminalNode* CACTParser::BasicTypeContext::Bool() {
  return getToken(CACTParser::Bool, 0);
}

tree::TerminalNode* CACTParser::BasicTypeContext::Float() {
  return getToken(CACTParser::Float, 0);
}

tree::TerminalNode* CACTParser::BasicTypeContext::Double() {
  return getToken(CACTParser::Double, 0);
}


size_t CACTParser::BasicTypeContext::getRuleIndex() const {
  return CACTParser::RuleBasicType;
}


std::any CACTParser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::BasicTypeContext* CACTParser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 4, CACTParser::RuleBasicType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 10512) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

CACTParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::LValueContext* CACTParser::PrimaryExpressionContext::lValue() {
  return getRuleContext<CACTParser::LValueContext>(0);
}

CACTParser::NumberContext* CACTParser::PrimaryExpressionContext::number() {
  return getRuleContext<CACTParser::NumberContext>(0);
}

tree::TerminalNode* CACTParser::PrimaryExpressionContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

CACTParser::ExpressionContext* CACTParser::PrimaryExpressionContext::expression() {
  return getRuleContext<CACTParser::ExpressionContext>(0);
}

tree::TerminalNode* CACTParser::PrimaryExpressionContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}


size_t CACTParser::PrimaryExpressionContext::getRuleIndex() const {
  return CACTParser::RulePrimaryExpression;
}


std::any CACTParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::PrimaryExpressionContext* CACTParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, CACTParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(105);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(99);
        lValue();
        break;
      }

      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant: {
        enterOuterAlt(_localctx, 2);
        setState(100);
        number();
        break;
      }

      case CACTParser::LeftParen: {
        enterOuterAlt(_localctx, 3);
        setState(101);
        match(CACTParser::LeftParen);
        setState(102);
        expression();
        setState(103);
        match(CACTParser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

CACTParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::PrimaryExpressionContext* CACTParser::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<CACTParser::PrimaryExpressionContext>(0);
}

CACTParser::UnaryOperatorContext* CACTParser::UnaryExpressionContext::unaryOperator() {
  return getRuleContext<CACTParser::UnaryOperatorContext>(0);
}

CACTParser::UnaryExpressionContext* CACTParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<CACTParser::UnaryExpressionContext>(0);
}

tree::TerminalNode* CACTParser::UnaryExpressionContext::Identifier() {
  return getToken(CACTParser::Identifier, 0);
}

tree::TerminalNode* CACTParser::UnaryExpressionContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

tree::TerminalNode* CACTParser::UnaryExpressionContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}

CACTParser::FunctionRParamsContext* CACTParser::UnaryExpressionContext::functionRParams() {
  return getRuleContext<CACTParser::FunctionRParamsContext>(0);
}


size_t CACTParser::UnaryExpressionContext::getRuleIndex() const {
  return CACTParser::RuleUnaryExpression;
}


std::any CACTParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::UnaryExpressionContext* CACTParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 8, CACTParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(117);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(107);
      primaryExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(108);
      unaryOperator();
      setState(109);
      unaryExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(111);
      match(CACTParser::Identifier);
      setState(112);
      match(CACTParser::LeftParen);
      setState(114);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4433211817998) != 0)) {
        setState(113);
        functionRParams();
      }
      setState(116);
      match(CACTParser::RightParen);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionRParamsContext ------------------------------------------------------------------

CACTParser::FunctionRParamsContext::FunctionRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::ExpressionContext *> CACTParser::FunctionRParamsContext::expression() {
  return getRuleContexts<CACTParser::ExpressionContext>();
}

CACTParser::ExpressionContext* CACTParser::FunctionRParamsContext::expression(size_t i) {
  return getRuleContext<CACTParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::FunctionRParamsContext::Comma() {
  return getTokens(CACTParser::Comma);
}

tree::TerminalNode* CACTParser::FunctionRParamsContext::Comma(size_t i) {
  return getToken(CACTParser::Comma, i);
}


size_t CACTParser::FunctionRParamsContext::getRuleIndex() const {
  return CACTParser::RuleFunctionRParams;
}


std::any CACTParser::FunctionRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFunctionRParams(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::FunctionRParamsContext* CACTParser::functionRParams() {
  FunctionRParamsContext *_localctx = _tracker.createInstance<FunctionRParamsContext>(_ctx, getState());
  enterRule(_localctx, 10, CACTParser::RuleFunctionRParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    expression();
    setState(124);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Comma) {
      setState(120);
      match(CACTParser::Comma);
      setState(121);
      expression();
      setState(126);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOperatorContext ------------------------------------------------------------------

CACTParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::AddOpContext* CACTParser::UnaryOperatorContext::addOp() {
  return getRuleContext<CACTParser::AddOpContext>(0);
}

tree::TerminalNode* CACTParser::UnaryOperatorContext::Not() {
  return getToken(CACTParser::Not, 0);
}


size_t CACTParser::UnaryOperatorContext::getRuleIndex() const {
  return CACTParser::RuleUnaryOperator;
}


std::any CACTParser::UnaryOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitUnaryOperator(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::UnaryOperatorContext* CACTParser::unaryOperator() {
  UnaryOperatorContext *_localctx = _tracker.createInstance<UnaryOperatorContext>(_ctx, getState());
  enterRule(_localctx, 12, CACTParser::RuleUnaryOperator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(129);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::Plus:
      case CACTParser::Minus: {
        enterOuterAlt(_localctx, 1);
        setState(127);
        addOp();
        break;
      }

      case CACTParser::Not: {
        enterOuterAlt(_localctx, 2);
        setState(128);
        match(CACTParser::Not);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddOpContext ------------------------------------------------------------------

CACTParser::AddOpContext::AddOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::AddOpContext::Plus() {
  return getToken(CACTParser::Plus, 0);
}

tree::TerminalNode* CACTParser::AddOpContext::Minus() {
  return getToken(CACTParser::Minus, 0);
}


size_t CACTParser::AddOpContext::getRuleIndex() const {
  return CACTParser::RuleAddOp;
}


std::any CACTParser::AddOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitAddOp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::AddOpContext* CACTParser::addOp() {
  AddOpContext *_localctx = _tracker.createInstance<AddOpContext>(_ctx, getState());
  enterRule(_localctx, 14, CACTParser::RuleAddOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    _la = _input->LA(1);
    if (!(_la == CACTParser::Plus

    || _la == CACTParser::Minus)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

CACTParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::UnaryExpressionContext *> CACTParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<CACTParser::UnaryExpressionContext>();
}

CACTParser::UnaryExpressionContext* CACTParser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<CACTParser::UnaryExpressionContext>(i);
}

std::vector<CACTParser::MultiplicativeOpContext *> CACTParser::MultiplicativeExpressionContext::multiplicativeOp() {
  return getRuleContexts<CACTParser::MultiplicativeOpContext>();
}

CACTParser::MultiplicativeOpContext* CACTParser::MultiplicativeExpressionContext::multiplicativeOp(size_t i) {
  return getRuleContext<CACTParser::MultiplicativeOpContext>(i);
}


size_t CACTParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return CACTParser::RuleMultiplicativeExpression;
}


std::any CACTParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::MultiplicativeExpressionContext* CACTParser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 16, CACTParser::RuleMultiplicativeExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    unaryExpression();
    setState(139);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7516192768) != 0)) {
      setState(134);
      multiplicativeOp();
      setState(135);
      unaryExpression();
      setState(141);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeOpContext ------------------------------------------------------------------

CACTParser::MultiplicativeOpContext::MultiplicativeOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::MultiplicativeOpContext::Star() {
  return getToken(CACTParser::Star, 0);
}

tree::TerminalNode* CACTParser::MultiplicativeOpContext::Div() {
  return getToken(CACTParser::Div, 0);
}

tree::TerminalNode* CACTParser::MultiplicativeOpContext::Mod() {
  return getToken(CACTParser::Mod, 0);
}


size_t CACTParser::MultiplicativeOpContext::getRuleIndex() const {
  return CACTParser::RuleMultiplicativeOp;
}


std::any CACTParser::MultiplicativeOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeOp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::MultiplicativeOpContext* CACTParser::multiplicativeOp() {
  MultiplicativeOpContext *_localctx = _tracker.createInstance<MultiplicativeOpContext>(_ctx, getState());
  enterRule(_localctx, 18, CACTParser::RuleMultiplicativeOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7516192768) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

CACTParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::MultiplicativeExpressionContext *> CACTParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContexts<CACTParser::MultiplicativeExpressionContext>();
}

CACTParser::MultiplicativeExpressionContext* CACTParser::AdditiveExpressionContext::multiplicativeExpression(size_t i) {
  return getRuleContext<CACTParser::MultiplicativeExpressionContext>(i);
}

std::vector<CACTParser::AdditiveOpContext *> CACTParser::AdditiveExpressionContext::additiveOp() {
  return getRuleContexts<CACTParser::AdditiveOpContext>();
}

CACTParser::AdditiveOpContext* CACTParser::AdditiveExpressionContext::additiveOp(size_t i) {
  return getRuleContext<CACTParser::AdditiveOpContext>(i);
}


size_t CACTParser::AdditiveExpressionContext::getRuleIndex() const {
  return CACTParser::RuleAdditiveExpression;
}


std::any CACTParser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::AdditiveExpressionContext* CACTParser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 20, CACTParser::RuleAdditiveExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
    multiplicativeExpression();
    setState(150);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Plus

    || _la == CACTParser::Minus) {
      setState(145);
      additiveOp();
      setState(146);
      multiplicativeExpression();
      setState(152);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveOpContext ------------------------------------------------------------------

CACTParser::AdditiveOpContext::AdditiveOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::AdditiveOpContext::Plus() {
  return getToken(CACTParser::Plus, 0);
}

tree::TerminalNode* CACTParser::AdditiveOpContext::Minus() {
  return getToken(CACTParser::Minus, 0);
}


size_t CACTParser::AdditiveOpContext::getRuleIndex() const {
  return CACTParser::RuleAdditiveOp;
}


std::any CACTParser::AdditiveOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitAdditiveOp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::AdditiveOpContext* CACTParser::additiveOp() {
  AdditiveOpContext *_localctx = _tracker.createInstance<AdditiveOpContext>(_ctx, getState());
  enterRule(_localctx, 22, CACTParser::RuleAdditiveOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    _la = _input->LA(1);
    if (!(_la == CACTParser::Plus

    || _la == CACTParser::Minus)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

CACTParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::AdditiveExpressionContext *> CACTParser::RelationalExpressionContext::additiveExpression() {
  return getRuleContexts<CACTParser::AdditiveExpressionContext>();
}

CACTParser::AdditiveExpressionContext* CACTParser::RelationalExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<CACTParser::AdditiveExpressionContext>(i);
}

CACTParser::RelationalOpContext* CACTParser::RelationalExpressionContext::relationalOp() {
  return getRuleContext<CACTParser::RelationalOpContext>(0);
}


size_t CACTParser::RelationalExpressionContext::getRuleIndex() const {
  return CACTParser::RuleRelationalExpression;
}


std::any CACTParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::RelationalExpressionContext* CACTParser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 24, CACTParser::RuleRelationalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    additiveExpression();
    setState(159);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 251658240) != 0)) {
      setState(156);
      relationalOp();
      setState(157);
      additiveExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalOpContext ------------------------------------------------------------------

CACTParser::RelationalOpContext::RelationalOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::RelationalOpContext::Less() {
  return getToken(CACTParser::Less, 0);
}

tree::TerminalNode* CACTParser::RelationalOpContext::Greater() {
  return getToken(CACTParser::Greater, 0);
}

tree::TerminalNode* CACTParser::RelationalOpContext::LessEqual() {
  return getToken(CACTParser::LessEqual, 0);
}

tree::TerminalNode* CACTParser::RelationalOpContext::GreaterEqual() {
  return getToken(CACTParser::GreaterEqual, 0);
}


size_t CACTParser::RelationalOpContext::getRuleIndex() const {
  return CACTParser::RuleRelationalOp;
}


std::any CACTParser::RelationalOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitRelationalOp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::RelationalOpContext* CACTParser::relationalOp() {
  RelationalOpContext *_localctx = _tracker.createInstance<RelationalOpContext>(_ctx, getState());
  enterRule(_localctx, 26, CACTParser::RuleRelationalOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 251658240) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

CACTParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::RelationalExpressionContext *> CACTParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContexts<CACTParser::RelationalExpressionContext>();
}

CACTParser::RelationalExpressionContext* CACTParser::EqualityExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<CACTParser::RelationalExpressionContext>(i);
}

CACTParser::EqualityOpContext* CACTParser::EqualityExpressionContext::equalityOp() {
  return getRuleContext<CACTParser::EqualityOpContext>(0);
}


size_t CACTParser::EqualityExpressionContext::getRuleIndex() const {
  return CACTParser::RuleEqualityExpression;
}


std::any CACTParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::EqualityExpressionContext* CACTParser::equalityExpression() {
  EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, getState());
  enterRule(_localctx, 28, CACTParser::RuleEqualityExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(163);
    relationalExpression();
    setState(167);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::Equal

    || _la == CACTParser::NotEqual) {
      setState(164);
      equalityOp();
      setState(165);
      relationalExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityOpContext ------------------------------------------------------------------

CACTParser::EqualityOpContext::EqualityOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::EqualityOpContext::Equal() {
  return getToken(CACTParser::Equal, 0);
}

tree::TerminalNode* CACTParser::EqualityOpContext::NotEqual() {
  return getToken(CACTParser::NotEqual, 0);
}


size_t CACTParser::EqualityOpContext::getRuleIndex() const {
  return CACTParser::RuleEqualityOp;
}


std::any CACTParser::EqualityOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitEqualityOp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::EqualityOpContext* CACTParser::equalityOp() {
  EqualityOpContext *_localctx = _tracker.createInstance<EqualityOpContext>(_ctx, getState());
  enterRule(_localctx, 30, CACTParser::RuleEqualityOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(169);
    _la = _input->LA(1);
    if (!(_la == CACTParser::Equal

    || _la == CACTParser::NotEqual)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

CACTParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::EqualityExpressionContext *> CACTParser::LogicalAndExpressionContext::equalityExpression() {
  return getRuleContexts<CACTParser::EqualityExpressionContext>();
}

CACTParser::EqualityExpressionContext* CACTParser::LogicalAndExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<CACTParser::EqualityExpressionContext>(i);
}

std::vector<CACTParser::LogicalAndOpContext *> CACTParser::LogicalAndExpressionContext::logicalAndOp() {
  return getRuleContexts<CACTParser::LogicalAndOpContext>();
}

CACTParser::LogicalAndOpContext* CACTParser::LogicalAndExpressionContext::logicalAndOp(size_t i) {
  return getRuleContext<CACTParser::LogicalAndOpContext>(i);
}


size_t CACTParser::LogicalAndExpressionContext::getRuleIndex() const {
  return CACTParser::RuleLogicalAndExpression;
}


std::any CACTParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::LogicalAndExpressionContext* CACTParser::logicalAndExpression() {
  LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, CACTParser::RuleLogicalAndExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(171);
    equalityExpression();
    setState(177);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::AndAnd) {
      setState(172);
      logicalAndOp();
      setState(173);
      equalityExpression();
      setState(179);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalAndOpContext ------------------------------------------------------------------

CACTParser::LogicalAndOpContext::LogicalAndOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::LogicalAndOpContext::AndAnd() {
  return getToken(CACTParser::AndAnd, 0);
}


size_t CACTParser::LogicalAndOpContext::getRuleIndex() const {
  return CACTParser::RuleLogicalAndOp;
}


std::any CACTParser::LogicalAndOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitLogicalAndOp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::LogicalAndOpContext* CACTParser::logicalAndOp() {
  LogicalAndOpContext *_localctx = _tracker.createInstance<LogicalAndOpContext>(_ctx, getState());
  enterRule(_localctx, 34, CACTParser::RuleLogicalAndOp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    match(CACTParser::AndAnd);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

CACTParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::LogicalAndExpressionContext *> CACTParser::LogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContexts<CACTParser::LogicalAndExpressionContext>();
}

CACTParser::LogicalAndExpressionContext* CACTParser::LogicalOrExpressionContext::logicalAndExpression(size_t i) {
  return getRuleContext<CACTParser::LogicalAndExpressionContext>(i);
}

std::vector<CACTParser::LogicalOrOpContext *> CACTParser::LogicalOrExpressionContext::logicalOrOp() {
  return getRuleContexts<CACTParser::LogicalOrOpContext>();
}

CACTParser::LogicalOrOpContext* CACTParser::LogicalOrExpressionContext::logicalOrOp(size_t i) {
  return getRuleContext<CACTParser::LogicalOrOpContext>(i);
}


size_t CACTParser::LogicalOrExpressionContext::getRuleIndex() const {
  return CACTParser::RuleLogicalOrExpression;
}


std::any CACTParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::LogicalOrExpressionContext* CACTParser::logicalOrExpression() {
  LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 36, CACTParser::RuleLogicalOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    logicalAndExpression();
    setState(188);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::OrOr) {
      setState(183);
      logicalOrOp();
      setState(184);
      logicalAndExpression();
      setState(190);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalOrOpContext ------------------------------------------------------------------

CACTParser::LogicalOrOpContext::LogicalOrOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::LogicalOrOpContext::OrOr() {
  return getToken(CACTParser::OrOr, 0);
}


size_t CACTParser::LogicalOrOpContext::getRuleIndex() const {
  return CACTParser::RuleLogicalOrOp;
}


std::any CACTParser::LogicalOrOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitLogicalOrOp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::LogicalOrOpContext* CACTParser::logicalOrOp() {
  LogicalOrOpContext *_localctx = _tracker.createInstance<LogicalOrOpContext>(_ctx, getState());
  enterRule(_localctx, 38, CACTParser::RuleLogicalOrOp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    match(CACTParser::OrOr);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CACTParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::AdditiveExpressionContext* CACTParser::ExpressionContext::additiveExpression() {
  return getRuleContext<CACTParser::AdditiveExpressionContext>(0);
}

tree::TerminalNode* CACTParser::ExpressionContext::BooleanConstant() {
  return getToken(CACTParser::BooleanConstant, 0);
}


size_t CACTParser::ExpressionContext::getRuleIndex() const {
  return CACTParser::RuleExpression;
}


std::any CACTParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ExpressionContext* CACTParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 40, CACTParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(195);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant:
      case CACTParser::LeftParen:
      case CACTParser::Plus:
      case CACTParser::Minus:
      case CACTParser::Not:
      case CACTParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(193);
        additiveExpression();
        break;
      }

      case CACTParser::BooleanConstant: {
        enterOuterAlt(_localctx, 2);
        setState(194);
        match(CACTParser::BooleanConstant);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantExpressionContext ------------------------------------------------------------------

CACTParser::ConstantExpressionContext::ConstantExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::NumberContext* CACTParser::ConstantExpressionContext::number() {
  return getRuleContext<CACTParser::NumberContext>(0);
}

CACTParser::AddOpContext* CACTParser::ConstantExpressionContext::addOp() {
  return getRuleContext<CACTParser::AddOpContext>(0);
}

tree::TerminalNode* CACTParser::ConstantExpressionContext::BooleanConstant() {
  return getToken(CACTParser::BooleanConstant, 0);
}


size_t CACTParser::ConstantExpressionContext::getRuleIndex() const {
  return CACTParser::RuleConstantExpression;
}


std::any CACTParser::ConstantExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitConstantExpression(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ConstantExpressionContext* CACTParser::constantExpression() {
  ConstantExpressionContext *_localctx = _tracker.createInstance<ConstantExpressionContext>(_ctx, getState());
  enterRule(_localctx, 42, CACTParser::RuleConstantExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(202);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant:
      case CACTParser::Plus:
      case CACTParser::Minus: {
        enterOuterAlt(_localctx, 1);
        setState(198);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CACTParser::Plus

        || _la == CACTParser::Minus) {
          setState(197);
          addOp();
        }
        setState(200);
        number();
        break;
      }

      case CACTParser::BooleanConstant: {
        enterOuterAlt(_localctx, 2);
        setState(201);
        match(CACTParser::BooleanConstant);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

CACTParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::LogicalOrExpressionContext* CACTParser::ConditionContext::logicalOrExpression() {
  return getRuleContext<CACTParser::LogicalOrExpressionContext>(0);
}


size_t CACTParser::ConditionContext::getRuleIndex() const {
  return CACTParser::RuleCondition;
}


std::any CACTParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ConditionContext* CACTParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 44, CACTParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(204);
    logicalOrExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

CACTParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::ConstantDeclarationContext* CACTParser::DeclarationContext::constantDeclaration() {
  return getRuleContext<CACTParser::ConstantDeclarationContext>(0);
}

CACTParser::VariableDeclarationContext* CACTParser::DeclarationContext::variableDeclaration() {
  return getRuleContext<CACTParser::VariableDeclarationContext>(0);
}


size_t CACTParser::DeclarationContext::getRuleIndex() const {
  return CACTParser::RuleDeclaration;
}


std::any CACTParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::DeclarationContext* CACTParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 46, CACTParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(208);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::Const: {
        enterOuterAlt(_localctx, 1);
        setState(206);
        constantDeclaration();
        break;
      }

      case CACTParser::Bool:
      case CACTParser::Double:
      case CACTParser::Float:
      case CACTParser::Int: {
        enterOuterAlt(_localctx, 2);
        setState(207);
        variableDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantDeclarationContext ------------------------------------------------------------------

CACTParser::ConstantDeclarationContext::ConstantDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::ConstantDeclarationContext::Const() {
  return getToken(CACTParser::Const, 0);
}

CACTParser::BasicTypeContext* CACTParser::ConstantDeclarationContext::basicType() {
  return getRuleContext<CACTParser::BasicTypeContext>(0);
}

std::vector<CACTParser::ConstantDefinitionContext *> CACTParser::ConstantDeclarationContext::constantDefinition() {
  return getRuleContexts<CACTParser::ConstantDefinitionContext>();
}

CACTParser::ConstantDefinitionContext* CACTParser::ConstantDeclarationContext::constantDefinition(size_t i) {
  return getRuleContext<CACTParser::ConstantDefinitionContext>(i);
}

tree::TerminalNode* CACTParser::ConstantDeclarationContext::Semi() {
  return getToken(CACTParser::Semi, 0);
}

std::vector<tree::TerminalNode *> CACTParser::ConstantDeclarationContext::Comma() {
  return getTokens(CACTParser::Comma);
}

tree::TerminalNode* CACTParser::ConstantDeclarationContext::Comma(size_t i) {
  return getToken(CACTParser::Comma, i);
}


size_t CACTParser::ConstantDeclarationContext::getRuleIndex() const {
  return CACTParser::RuleConstantDeclaration;
}


std::any CACTParser::ConstantDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitConstantDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ConstantDeclarationContext* CACTParser::constantDeclaration() {
  ConstantDeclarationContext *_localctx = _tracker.createInstance<ConstantDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 48, CACTParser::RuleConstantDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(210);
    match(CACTParser::Const);
    setState(211);
    basicType();
    setState(212);
    constantDefinition();
    setState(217);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Comma) {
      setState(213);
      match(CACTParser::Comma);
      setState(214);
      constantDefinition();
      setState(219);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(220);
    match(CACTParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantDefinitionContext ------------------------------------------------------------------

CACTParser::ConstantDefinitionContext::ConstantDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::ConstantDefinitionContext::Identifier() {
  return getToken(CACTParser::Identifier, 0);
}

tree::TerminalNode* CACTParser::ConstantDefinitionContext::Assign() {
  return getToken(CACTParser::Assign, 0);
}

CACTParser::ConstantInitValueContext* CACTParser::ConstantDefinitionContext::constantInitValue() {
  return getRuleContext<CACTParser::ConstantInitValueContext>(0);
}

std::vector<tree::TerminalNode *> CACTParser::ConstantDefinitionContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::ConstantDefinitionContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CACTParser::ConstantDefinitionContext::IntegerConstant() {
  return getTokens(CACTParser::IntegerConstant);
}

tree::TerminalNode* CACTParser::ConstantDefinitionContext::IntegerConstant(size_t i) {
  return getToken(CACTParser::IntegerConstant, i);
}

std::vector<tree::TerminalNode *> CACTParser::ConstantDefinitionContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::ConstantDefinitionContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
}


size_t CACTParser::ConstantDefinitionContext::getRuleIndex() const {
  return CACTParser::RuleConstantDefinition;
}


std::any CACTParser::ConstantDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitConstantDefinition(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ConstantDefinitionContext* CACTParser::constantDefinition() {
  ConstantDefinitionContext *_localctx = _tracker.createInstance<ConstantDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 50, CACTParser::RuleConstantDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(222);
    match(CACTParser::Identifier);
    setState(228);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::LeftBracket) {
      setState(223);
      match(CACTParser::LeftBracket);
      setState(224);
      match(CACTParser::IntegerConstant);
      setState(225);
      match(CACTParser::RightBracket);
      setState(230);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(231);
    match(CACTParser::Assign);
    setState(232);
    constantInitValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantInitValueContext ------------------------------------------------------------------

CACTParser::ConstantInitValueContext::ConstantInitValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::ConstantExpressionContext* CACTParser::ConstantInitValueContext::constantExpression() {
  return getRuleContext<CACTParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* CACTParser::ConstantInitValueContext::LeftBrace() {
  return getToken(CACTParser::LeftBrace, 0);
}

tree::TerminalNode* CACTParser::ConstantInitValueContext::RightBrace() {
  return getToken(CACTParser::RightBrace, 0);
}

std::vector<CACTParser::ConstantInitValueContext *> CACTParser::ConstantInitValueContext::constantInitValue() {
  return getRuleContexts<CACTParser::ConstantInitValueContext>();
}

CACTParser::ConstantInitValueContext* CACTParser::ConstantInitValueContext::constantInitValue(size_t i) {
  return getRuleContext<CACTParser::ConstantInitValueContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::ConstantInitValueContext::Comma() {
  return getTokens(CACTParser::Comma);
}

tree::TerminalNode* CACTParser::ConstantInitValueContext::Comma(size_t i) {
  return getToken(CACTParser::Comma, i);
}


size_t CACTParser::ConstantInitValueContext::getRuleIndex() const {
  return CACTParser::RuleConstantInitValue;
}


std::any CACTParser::ConstantInitValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitConstantInitValue(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ConstantInitValueContext* CACTParser::constantInitValue() {
  ConstantInitValueContext *_localctx = _tracker.createInstance<ConstantInitValueContext>(_ctx, getState());
  enterRule(_localctx, 52, CACTParser::RuleConstantInitValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(247);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant:
      case CACTParser::BooleanConstant:
      case CACTParser::Plus:
      case CACTParser::Minus: {
        enterOuterAlt(_localctx, 1);
        setState(234);
        constantExpression();
        break;
      }

      case CACTParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(235);
        match(CACTParser::LeftBrace);
        setState(244);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 809500686) != 0)) {
          setState(236);
          constantInitValue();
          setState(241);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == CACTParser::Comma) {
            setState(237);
            match(CACTParser::Comma);
            setState(238);
            constantInitValue();
            setState(243);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(246);
        match(CACTParser::RightBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

CACTParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::BasicTypeContext* CACTParser::VariableDeclarationContext::basicType() {
  return getRuleContext<CACTParser::BasicTypeContext>(0);
}

std::vector<CACTParser::VariableDefinitionContext *> CACTParser::VariableDeclarationContext::variableDefinition() {
  return getRuleContexts<CACTParser::VariableDefinitionContext>();
}

CACTParser::VariableDefinitionContext* CACTParser::VariableDeclarationContext::variableDefinition(size_t i) {
  return getRuleContext<CACTParser::VariableDefinitionContext>(i);
}

tree::TerminalNode* CACTParser::VariableDeclarationContext::Semi() {
  return getToken(CACTParser::Semi, 0);
}

std::vector<tree::TerminalNode *> CACTParser::VariableDeclarationContext::Comma() {
  return getTokens(CACTParser::Comma);
}

tree::TerminalNode* CACTParser::VariableDeclarationContext::Comma(size_t i) {
  return getToken(CACTParser::Comma, i);
}


size_t CACTParser::VariableDeclarationContext::getRuleIndex() const {
  return CACTParser::RuleVariableDeclaration;
}


std::any CACTParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::VariableDeclarationContext* CACTParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 54, CACTParser::RuleVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(249);
    basicType();
    setState(250);
    variableDefinition();
    setState(255);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Comma) {
      setState(251);
      match(CACTParser::Comma);
      setState(252);
      variableDefinition();
      setState(257);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(258);
    match(CACTParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDefinitionContext ------------------------------------------------------------------

CACTParser::VariableDefinitionContext::VariableDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::VariableDefinitionContext::Identifier() {
  return getToken(CACTParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CACTParser::VariableDefinitionContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::VariableDefinitionContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CACTParser::VariableDefinitionContext::IntegerConstant() {
  return getTokens(CACTParser::IntegerConstant);
}

tree::TerminalNode* CACTParser::VariableDefinitionContext::IntegerConstant(size_t i) {
  return getToken(CACTParser::IntegerConstant, i);
}

std::vector<tree::TerminalNode *> CACTParser::VariableDefinitionContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::VariableDefinitionContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
}

tree::TerminalNode* CACTParser::VariableDefinitionContext::Assign() {
  return getToken(CACTParser::Assign, 0);
}

CACTParser::ConstantInitValueContext* CACTParser::VariableDefinitionContext::constantInitValue() {
  return getRuleContext<CACTParser::ConstantInitValueContext>(0);
}


size_t CACTParser::VariableDefinitionContext::getRuleIndex() const {
  return CACTParser::RuleVariableDefinition;
}


std::any CACTParser::VariableDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitVariableDefinition(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::VariableDefinitionContext* CACTParser::variableDefinition() {
  VariableDefinitionContext *_localctx = _tracker.createInstance<VariableDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 56, CACTParser::RuleVariableDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(260);
    match(CACTParser::Identifier);
    setState(266);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::LeftBracket) {
      setState(261);
      match(CACTParser::LeftBracket);
      setState(262);
      match(CACTParser::IntegerConstant);
      setState(263);
      match(CACTParser::RightBracket);
      setState(268);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(271);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::Assign) {
      setState(269);
      match(CACTParser::Assign);
      setState(270);
      constantInitValue();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CACTParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::CompoundStatementContext* CACTParser::StatementContext::compoundStatement() {
  return getRuleContext<CACTParser::CompoundStatementContext>(0);
}

CACTParser::ExpressionStatementContext* CACTParser::StatementContext::expressionStatement() {
  return getRuleContext<CACTParser::ExpressionStatementContext>(0);
}

CACTParser::SelectionStatementContext* CACTParser::StatementContext::selectionStatement() {
  return getRuleContext<CACTParser::SelectionStatementContext>(0);
}

CACTParser::IterationStatementContext* CACTParser::StatementContext::iterationStatement() {
  return getRuleContext<CACTParser::IterationStatementContext>(0);
}

CACTParser::JumpStatementContext* CACTParser::StatementContext::jumpStatement() {
  return getRuleContext<CACTParser::JumpStatementContext>(0);
}


size_t CACTParser::StatementContext::getRuleIndex() const {
  return CACTParser::RuleStatement;
}


std::any CACTParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::StatementContext* CACTParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 58, CACTParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(278);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::LeftBrace: {
        enterOuterAlt(_localctx, 1);
        setState(273);
        compoundStatement();
        break;
      }

      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant:
      case CACTParser::BooleanConstant:
      case CACTParser::LeftParen:
      case CACTParser::Plus:
      case CACTParser::Minus:
      case CACTParser::Not:
      case CACTParser::Semi:
      case CACTParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(274);
        expressionStatement();
        break;
      }

      case CACTParser::If: {
        enterOuterAlt(_localctx, 3);
        setState(275);
        selectionStatement();
        break;
      }

      case CACTParser::While: {
        enterOuterAlt(_localctx, 4);
        setState(276);
        iterationStatement();
        break;
      }

      case CACTParser::Break:
      case CACTParser::Continue:
      case CACTParser::Return: {
        enterOuterAlt(_localctx, 5);
        setState(277);
        jumpStatement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompoundStatementContext ------------------------------------------------------------------

CACTParser::CompoundStatementContext::CompoundStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::CompoundStatementContext::LeftBrace() {
  return getToken(CACTParser::LeftBrace, 0);
}

tree::TerminalNode* CACTParser::CompoundStatementContext::RightBrace() {
  return getToken(CACTParser::RightBrace, 0);
}

CACTParser::BlockItemListContext* CACTParser::CompoundStatementContext::blockItemList() {
  return getRuleContext<CACTParser::BlockItemListContext>(0);
}


size_t CACTParser::CompoundStatementContext::getRuleIndex() const {
  return CACTParser::RuleCompoundStatement;
}


std::any CACTParser::CompoundStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitCompoundStatement(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::CompoundStatementContext* CACTParser::compoundStatement() {
  CompoundStatementContext *_localctx = _tracker.createInstance<CompoundStatementContext>(_ctx, getState());
  enterRule(_localctx, 60, CACTParser::RuleCompoundStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    match(CACTParser::LeftBrace);
    setState(282);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4501935651326) != 0)) {
      setState(281);
      blockItemList();
    }
    setState(284);
    match(CACTParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemListContext ------------------------------------------------------------------

CACTParser::BlockItemListContext::BlockItemListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::BlockItemContext *> CACTParser::BlockItemListContext::blockItem() {
  return getRuleContexts<CACTParser::BlockItemContext>();
}

CACTParser::BlockItemContext* CACTParser::BlockItemListContext::blockItem(size_t i) {
  return getRuleContext<CACTParser::BlockItemContext>(i);
}


size_t CACTParser::BlockItemListContext::getRuleIndex() const {
  return CACTParser::RuleBlockItemList;
}


std::any CACTParser::BlockItemListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitBlockItemList(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::BlockItemListContext* CACTParser::blockItemList() {
  BlockItemListContext *_localctx = _tracker.createInstance<BlockItemListContext>(_ctx, getState());
  enterRule(_localctx, 62, CACTParser::RuleBlockItemList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(287); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(286);
      blockItem();
      setState(289); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4501935651326) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

CACTParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::StatementContext* CACTParser::BlockItemContext::statement() {
  return getRuleContext<CACTParser::StatementContext>(0);
}

CACTParser::DeclarationContext* CACTParser::BlockItemContext::declaration() {
  return getRuleContext<CACTParser::DeclarationContext>(0);
}


size_t CACTParser::BlockItemContext::getRuleIndex() const {
  return CACTParser::RuleBlockItem;
}


std::any CACTParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::BlockItemContext* CACTParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 64, CACTParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(293);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant:
      case CACTParser::BooleanConstant:
      case CACTParser::Break:
      case CACTParser::Continue:
      case CACTParser::If:
      case CACTParser::Return:
      case CACTParser::While:
      case CACTParser::LeftParen:
      case CACTParser::LeftBrace:
      case CACTParser::Plus:
      case CACTParser::Minus:
      case CACTParser::Not:
      case CACTParser::Semi:
      case CACTParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(291);
        statement();
        break;
      }

      case CACTParser::Bool:
      case CACTParser::Const:
      case CACTParser::Double:
      case CACTParser::Float:
      case CACTParser::Int: {
        enterOuterAlt(_localctx, 2);
        setState(292);
        declaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

CACTParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::ExpressionStatementContext::Semi() {
  return getToken(CACTParser::Semi, 0);
}

CACTParser::ExpressionContext* CACTParser::ExpressionStatementContext::expression() {
  return getRuleContext<CACTParser::ExpressionContext>(0);
}

CACTParser::LValueContext* CACTParser::ExpressionStatementContext::lValue() {
  return getRuleContext<CACTParser::LValueContext>(0);
}

tree::TerminalNode* CACTParser::ExpressionStatementContext::Assign() {
  return getToken(CACTParser::Assign, 0);
}


size_t CACTParser::ExpressionStatementContext::getRuleIndex() const {
  return CACTParser::RuleExpressionStatement;
}


std::any CACTParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ExpressionStatementContext* CACTParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 66, CACTParser::RuleExpressionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(304);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(296);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4433211817998) != 0)) {
        setState(295);
        expression();
      }
      setState(298);
      match(CACTParser::Semi);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(299);
      lValue();
      setState(300);
      match(CACTParser::Assign);
      setState(301);
      expression();
      setState(302);
      match(CACTParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValueContext ------------------------------------------------------------------

CACTParser::LValueContext::LValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::LValueContext::Identifier() {
  return getToken(CACTParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CACTParser::LValueContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::LValueContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<CACTParser::ExpressionContext *> CACTParser::LValueContext::expression() {
  return getRuleContexts<CACTParser::ExpressionContext>();
}

CACTParser::ExpressionContext* CACTParser::LValueContext::expression(size_t i) {
  return getRuleContext<CACTParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::LValueContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::LValueContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
}


size_t CACTParser::LValueContext::getRuleIndex() const {
  return CACTParser::RuleLValue;
}


std::any CACTParser::LValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitLValue(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::LValueContext* CACTParser::lValue() {
  LValueContext *_localctx = _tracker.createInstance<LValueContext>(_ctx, getState());
  enterRule(_localctx, 68, CACTParser::RuleLValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(306);
    match(CACTParser::Identifier);
    setState(313);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::LeftBracket) {
      setState(307);
      match(CACTParser::LeftBracket);
      setState(308);
      expression();
      setState(309);
      match(CACTParser::RightBracket);
      setState(315);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectionStatementContext ------------------------------------------------------------------

CACTParser::SelectionStatementContext::SelectionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::SelectionStatementContext::If() {
  return getToken(CACTParser::If, 0);
}

tree::TerminalNode* CACTParser::SelectionStatementContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

CACTParser::ConditionContext* CACTParser::SelectionStatementContext::condition() {
  return getRuleContext<CACTParser::ConditionContext>(0);
}

tree::TerminalNode* CACTParser::SelectionStatementContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}

std::vector<CACTParser::StatementContext *> CACTParser::SelectionStatementContext::statement() {
  return getRuleContexts<CACTParser::StatementContext>();
}

CACTParser::StatementContext* CACTParser::SelectionStatementContext::statement(size_t i) {
  return getRuleContext<CACTParser::StatementContext>(i);
}

tree::TerminalNode* CACTParser::SelectionStatementContext::Else() {
  return getToken(CACTParser::Else, 0);
}


size_t CACTParser::SelectionStatementContext::getRuleIndex() const {
  return CACTParser::RuleSelectionStatement;
}


std::any CACTParser::SelectionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitSelectionStatement(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::SelectionStatementContext* CACTParser::selectionStatement() {
  SelectionStatementContext *_localctx = _tracker.createInstance<SelectionStatementContext>(_ctx, getState());
  enterRule(_localctx, 70, CACTParser::RuleSelectionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(316);
    match(CACTParser::If);
    setState(317);
    match(CACTParser::LeftParen);
    setState(318);
    condition();
    setState(319);
    match(CACTParser::RightParen);
    setState(320);
    statement();
    setState(323);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      setState(321);
      match(CACTParser::Else);
      setState(322);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IterationStatementContext ------------------------------------------------------------------

CACTParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::IterationStatementContext::While() {
  return getToken(CACTParser::While, 0);
}

tree::TerminalNode* CACTParser::IterationStatementContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

CACTParser::ConditionContext* CACTParser::IterationStatementContext::condition() {
  return getRuleContext<CACTParser::ConditionContext>(0);
}

tree::TerminalNode* CACTParser::IterationStatementContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}

CACTParser::StatementContext* CACTParser::IterationStatementContext::statement() {
  return getRuleContext<CACTParser::StatementContext>(0);
}


size_t CACTParser::IterationStatementContext::getRuleIndex() const {
  return CACTParser::RuleIterationStatement;
}


std::any CACTParser::IterationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitIterationStatement(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::IterationStatementContext* CACTParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 72, CACTParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    match(CACTParser::While);
    setState(326);
    match(CACTParser::LeftParen);
    setState(327);
    condition();
    setState(328);
    match(CACTParser::RightParen);
    setState(329);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JumpStatementContext ------------------------------------------------------------------

CACTParser::JumpStatementContext::JumpStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::JumpStatementContext::Semi() {
  return getToken(CACTParser::Semi, 0);
}

tree::TerminalNode* CACTParser::JumpStatementContext::Continue() {
  return getToken(CACTParser::Continue, 0);
}

tree::TerminalNode* CACTParser::JumpStatementContext::Break() {
  return getToken(CACTParser::Break, 0);
}

tree::TerminalNode* CACTParser::JumpStatementContext::Return() {
  return getToken(CACTParser::Return, 0);
}

CACTParser::ExpressionContext* CACTParser::JumpStatementContext::expression() {
  return getRuleContext<CACTParser::ExpressionContext>(0);
}


size_t CACTParser::JumpStatementContext::getRuleIndex() const {
  return CACTParser::RuleJumpStatement;
}


std::any CACTParser::JumpStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitJumpStatement(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::JumpStatementContext* CACTParser::jumpStatement() {
  JumpStatementContext *_localctx = _tracker.createInstance<JumpStatementContext>(_ctx, getState());
  enterRule(_localctx, 74, CACTParser::RuleJumpStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::Continue: {
        setState(331);
        match(CACTParser::Continue);
        break;
      }

      case CACTParser::Break: {
        setState(332);
        match(CACTParser::Break);
        break;
      }

      case CACTParser::Return: {
        setState(333);
        match(CACTParser::Return);
        setState(335);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4433211817998) != 0)) {
          setState(334);
          expression();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(339);
    match(CACTParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TranslationUnitContext ------------------------------------------------------------------

CACTParser::TranslationUnitContext::TranslationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::ExternalDeclarationContext *> CACTParser::TranslationUnitContext::externalDeclaration() {
  return getRuleContexts<CACTParser::ExternalDeclarationContext>();
}

CACTParser::ExternalDeclarationContext* CACTParser::TranslationUnitContext::externalDeclaration(size_t i) {
  return getRuleContext<CACTParser::ExternalDeclarationContext>(i);
}


size_t CACTParser::TranslationUnitContext::getRuleIndex() const {
  return CACTParser::RuleTranslationUnit;
}


std::any CACTParser::TranslationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitTranslationUnit(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::TranslationUnitContext* CACTParser::translationUnit() {
  TranslationUnitContext *_localctx = _tracker.createInstance<TranslationUnitContext>(_ctx, getState());
  enterRule(_localctx, 76, CACTParser::RuleTranslationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(342); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(341);
      externalDeclaration();
      setState(344); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 76112) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternalDeclarationContext ------------------------------------------------------------------

CACTParser::ExternalDeclarationContext::ExternalDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::FunctionDefinitionContext* CACTParser::ExternalDeclarationContext::functionDefinition() {
  return getRuleContext<CACTParser::FunctionDefinitionContext>(0);
}

CACTParser::DeclarationContext* CACTParser::ExternalDeclarationContext::declaration() {
  return getRuleContext<CACTParser::DeclarationContext>(0);
}


size_t CACTParser::ExternalDeclarationContext::getRuleIndex() const {
  return CACTParser::RuleExternalDeclaration;
}


std::any CACTParser::ExternalDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitExternalDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ExternalDeclarationContext* CACTParser::externalDeclaration() {
  ExternalDeclarationContext *_localctx = _tracker.createInstance<ExternalDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 78, CACTParser::RuleExternalDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(348);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(346);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(347);
      declaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

CACTParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::FunctionTypeContext* CACTParser::FunctionDefinitionContext::functionType() {
  return getRuleContext<CACTParser::FunctionTypeContext>(0);
}

tree::TerminalNode* CACTParser::FunctionDefinitionContext::Identifier() {
  return getToken(CACTParser::Identifier, 0);
}

tree::TerminalNode* CACTParser::FunctionDefinitionContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

tree::TerminalNode* CACTParser::FunctionDefinitionContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}

CACTParser::CompoundStatementContext* CACTParser::FunctionDefinitionContext::compoundStatement() {
  return getRuleContext<CACTParser::CompoundStatementContext>(0);
}

CACTParser::FunctionFParamsContext* CACTParser::FunctionDefinitionContext::functionFParams() {
  return getRuleContext<CACTParser::FunctionFParamsContext>(0);
}


size_t CACTParser::FunctionDefinitionContext::getRuleIndex() const {
  return CACTParser::RuleFunctionDefinition;
}


std::any CACTParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::FunctionDefinitionContext* CACTParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 80, CACTParser::RuleFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(350);
    functionType();
    setState(351);
    match(CACTParser::Identifier);
    setState(352);
    match(CACTParser::LeftParen);
    setState(354);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 10512) != 0)) {
      setState(353);
      functionFParams();
    }
    setState(356);
    match(CACTParser::RightParen);
    setState(357);
    compoundStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionFParamsContext ------------------------------------------------------------------

CACTParser::FunctionFParamsContext::FunctionFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::FunctionFParamContext *> CACTParser::FunctionFParamsContext::functionFParam() {
  return getRuleContexts<CACTParser::FunctionFParamContext>();
}

CACTParser::FunctionFParamContext* CACTParser::FunctionFParamsContext::functionFParam(size_t i) {
  return getRuleContext<CACTParser::FunctionFParamContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::FunctionFParamsContext::Comma() {
  return getTokens(CACTParser::Comma);
}

tree::TerminalNode* CACTParser::FunctionFParamsContext::Comma(size_t i) {
  return getToken(CACTParser::Comma, i);
}


size_t CACTParser::FunctionFParamsContext::getRuleIndex() const {
  return CACTParser::RuleFunctionFParams;
}


std::any CACTParser::FunctionFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFunctionFParams(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::FunctionFParamsContext* CACTParser::functionFParams() {
  FunctionFParamsContext *_localctx = _tracker.createInstance<FunctionFParamsContext>(_ctx, getState());
  enterRule(_localctx, 82, CACTParser::RuleFunctionFParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(359);
    functionFParam();
    setState(364);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Comma) {
      setState(360);
      match(CACTParser::Comma);
      setState(361);
      functionFParam();
      setState(366);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionFParamContext ------------------------------------------------------------------

CACTParser::FunctionFParamContext::FunctionFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::BasicTypeContext* CACTParser::FunctionFParamContext::basicType() {
  return getRuleContext<CACTParser::BasicTypeContext>(0);
}

tree::TerminalNode* CACTParser::FunctionFParamContext::Identifier() {
  return getToken(CACTParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CACTParser::FunctionFParamContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::FunctionFParamContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CACTParser::FunctionFParamContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::FunctionFParamContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
}

std::vector<tree::TerminalNode *> CACTParser::FunctionFParamContext::IntegerConstant() {
  return getTokens(CACTParser::IntegerConstant);
}

tree::TerminalNode* CACTParser::FunctionFParamContext::IntegerConstant(size_t i) {
  return getToken(CACTParser::IntegerConstant, i);
}


size_t CACTParser::FunctionFParamContext::getRuleIndex() const {
  return CACTParser::RuleFunctionFParam;
}


std::any CACTParser::FunctionFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFunctionFParam(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::FunctionFParamContext* CACTParser::functionFParam() {
  FunctionFParamContext *_localctx = _tracker.createInstance<FunctionFParamContext>(_ctx, getState());
  enterRule(_localctx, 84, CACTParser::RuleFunctionFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(367);
    basicType();
    setState(368);
    match(CACTParser::Identifier);
    setState(384);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::LeftBracket) {
      setState(369);
      match(CACTParser::LeftBracket);
      setState(371);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CACTParser::IntegerConstant) {
        setState(370);
        match(CACTParser::IntegerConstant);
      }
      setState(373);
      match(CACTParser::RightBracket);
      setState(381);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CACTParser::LeftBracket) {
        setState(374);
        match(CACTParser::LeftBracket);
        setState(376);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CACTParser::IntegerConstant) {
          setState(375);
          match(CACTParser::IntegerConstant);
        }
        setState(378);
        match(CACTParser::RightBracket);
        setState(383);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

CACTParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CACTParser::NumberContext::getRuleIndex() const {
  return CACTParser::RuleNumber;
}

void CACTParser::NumberContext::copyFrom(NumberContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FloatingConstantContext ------------------------------------------------------------------

tree::TerminalNode* CACTParser::FloatingConstantContext::FloatingConstant() {
  return getToken(CACTParser::FloatingConstant, 0);
}

CACTParser::FloatingConstantContext::FloatingConstantContext(NumberContext *ctx) { copyFrom(ctx); }


std::any CACTParser::FloatingConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFloatingConstant(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntegerConstantContext ------------------------------------------------------------------

tree::TerminalNode* CACTParser::IntegerConstantContext::IntegerConstant() {
  return getToken(CACTParser::IntegerConstant, 0);
}

CACTParser::IntegerConstantContext::IntegerConstantContext(NumberContext *ctx) { copyFrom(ctx); }


std::any CACTParser::IntegerConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitIntegerConstant(this);
  else
    return visitor->visitChildren(this);
}
CACTParser::NumberContext* CACTParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 86, CACTParser::RuleNumber);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(388);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntegerConstant: {
        _localctx = _tracker.createInstance<CACTParser::IntegerConstantContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(386);
        match(CACTParser::IntegerConstant);
        break;
      }

      case CACTParser::FloatingConstant: {
        _localctx = _tracker.createInstance<CACTParser::FloatingConstantContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(387);
        match(CACTParser::FloatingConstant);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void CACTParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  cactParserInitialize();
#else
  ::antlr4::internal::call_once(cactParserOnceFlag, cactParserInitialize);
#endif
}

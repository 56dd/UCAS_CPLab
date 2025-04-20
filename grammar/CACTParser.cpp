
    #include <vector>
    #include <string>


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
      "functionType", "basicType", "primaryExpression", "unaryExpression", 
      "unaryOperator", "functionRParams", "additiveExpression", "multiplicativeExpression", 
      "relationalExpression", "equalityExpression", "logicalAndExpression", 
      "logicalOrExpression", "condition", "constantExpression", "constantInitValue", 
      "expression", "declaration", "constantDeclaration", "constantDefinition", 
      "variableDeclaration", "variableDefinition", "statement", "compoundStatement", 
      "expressionStatement", "selectionStatement", "iterationStatement", 
      "jumpStatement", "blockItem", "blockItemList", "leftValue", "compilationUnit", 
      "translationUnit", "externalDeclaration", "functionDefinition", "functionFParams", 
      "functionFParam", "number"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "'const'", "'continue'", "'while'", 
      "'break'", "'true'", "'false'", "'if'", "'else'", "'void'", "'int'", 
      "'char'", "'float'", "'double'", "'return'", "'('", "')'", "'['", 
      "']'", "'{'", "'}'", "'<'", "'<='", "'>'", "'>='", "'+'", "'-'", "'*'", 
      "'/'", "'%'", "'&&'", "'||'", "'!'", "';'", "','", "'='", "'=='", 
      "'!='", "'.'"
    },
    std::vector<std::string>{
      "", "Whitespace", "Newline", "CommentLine", "CommentBlock", "IntegerConstant", 
      "FloatingConstant", "CharacterConstant", "Const", "Continue", "While", 
      "Break", "True", "False", "If", "Else", "Void", "Int", "Char", "Float", 
      "Double", "Return", "LeftParenthesis", "RightParenthesis", "LeftBracket", 
      "RightBracket", "LeftBrace", "RightBrace", "Less", "LessEqual", "Greater", 
      "GreaterEqual", "Plus", "Minus", "Star", "Div", "Mod", "AndAnd", "OrOr", 
      "Not", "Semicolon", "Comma", "Assign", "Equal", "NotEqual", "Dot", 
      "Identifier"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,46,349,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,1,0,1,0,3,0,77,8,0,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,
  	2,88,8,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,97,8,3,1,3,3,3,100,8,3,1,4,1,
  	4,1,5,1,5,1,5,5,5,107,8,5,10,5,12,5,110,9,5,1,6,1,6,1,6,5,6,115,8,6,10,
  	6,12,6,118,9,6,1,7,1,7,1,7,5,7,123,8,7,10,7,12,7,126,9,7,1,8,1,8,1,8,
  	3,8,131,8,8,1,9,1,9,1,9,3,9,136,8,9,1,10,1,10,1,10,5,10,141,8,10,10,10,
  	12,10,144,9,10,1,11,1,11,1,11,5,11,149,8,11,10,11,12,11,152,9,11,1,12,
  	1,12,1,13,1,13,3,13,158,8,13,1,14,1,14,1,14,1,14,1,14,5,14,165,8,14,10,
  	14,12,14,168,9,14,3,14,170,8,14,1,14,3,14,173,8,14,1,15,1,15,1,16,1,16,
  	3,16,179,8,16,1,17,1,17,1,17,1,17,1,17,5,17,186,8,17,10,17,12,17,189,
  	9,17,1,17,1,17,1,18,1,18,1,18,1,18,5,18,197,8,18,10,18,12,18,200,9,18,
  	1,18,1,18,1,18,1,19,1,19,1,19,1,19,5,19,209,8,19,10,19,12,19,212,9,19,
  	1,19,1,19,1,20,1,20,1,20,1,20,5,20,220,8,20,10,20,12,20,223,9,20,1,20,
  	1,20,3,20,227,8,20,1,21,1,21,1,21,1,21,1,21,3,21,234,8,21,1,22,1,22,3,
  	22,238,8,22,1,22,1,22,1,23,3,23,243,8,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	3,23,251,8,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,260,8,24,1,25,1,
  	25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,3,26,272,8,26,3,26,274,8,26,
  	1,26,1,26,1,27,1,27,3,27,280,8,27,1,28,4,28,283,8,28,11,28,12,28,284,
  	1,29,1,29,1,29,1,29,1,29,5,29,292,8,29,10,29,12,29,295,9,29,1,30,3,30,
  	298,8,30,1,30,1,30,1,31,4,31,303,8,31,11,31,12,31,304,1,32,1,32,3,32,
  	309,8,32,1,33,1,33,1,33,1,33,3,33,315,8,33,1,33,1,33,1,33,1,34,1,34,1,
  	34,5,34,323,8,34,10,34,12,34,326,9,34,1,35,1,35,1,35,1,35,3,35,332,8,
  	35,1,35,1,35,1,35,3,35,337,8,35,1,35,5,35,340,8,35,10,35,12,35,343,9,
  	35,3,35,345,8,35,1,36,1,36,1,36,0,0,37,0,2,4,6,8,10,12,14,16,18,20,22,
  	24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,
  	70,72,0,7,1,0,17,20,2,0,32,33,39,39,1,0,32,33,1,0,34,36,1,0,28,31,1,0,
  	43,44,1,0,5,6,358,0,76,1,0,0,0,2,78,1,0,0,0,4,87,1,0,0,0,6,99,1,0,0,0,
  	8,101,1,0,0,0,10,103,1,0,0,0,12,111,1,0,0,0,14,119,1,0,0,0,16,127,1,0,
  	0,0,18,132,1,0,0,0,20,137,1,0,0,0,22,145,1,0,0,0,24,153,1,0,0,0,26,157,
  	1,0,0,0,28,172,1,0,0,0,30,174,1,0,0,0,32,178,1,0,0,0,34,180,1,0,0,0,36,
  	192,1,0,0,0,38,204,1,0,0,0,40,215,1,0,0,0,42,233,1,0,0,0,44,235,1,0,0,
  	0,46,250,1,0,0,0,48,252,1,0,0,0,50,261,1,0,0,0,52,273,1,0,0,0,54,279,
  	1,0,0,0,56,282,1,0,0,0,58,286,1,0,0,0,60,297,1,0,0,0,62,302,1,0,0,0,64,
  	308,1,0,0,0,66,310,1,0,0,0,68,319,1,0,0,0,70,327,1,0,0,0,72,346,1,0,0,
  	0,74,77,5,16,0,0,75,77,3,2,1,0,76,74,1,0,0,0,76,75,1,0,0,0,77,1,1,0,0,
  	0,78,79,7,0,0,0,79,3,1,0,0,0,80,88,3,58,29,0,81,88,3,72,36,0,82,88,5,
  	7,0,0,83,84,5,22,0,0,84,85,3,30,15,0,85,86,5,23,0,0,86,88,1,0,0,0,87,
  	80,1,0,0,0,87,81,1,0,0,0,87,82,1,0,0,0,87,83,1,0,0,0,88,5,1,0,0,0,89,
  	100,3,4,2,0,90,91,3,8,4,0,91,92,3,6,3,0,92,100,1,0,0,0,93,94,5,46,0,0,
  	94,96,5,22,0,0,95,97,3,10,5,0,96,95,1,0,0,0,96,97,1,0,0,0,97,98,1,0,0,
  	0,98,100,5,23,0,0,99,89,1,0,0,0,99,90,1,0,0,0,99,93,1,0,0,0,100,7,1,0,
  	0,0,101,102,7,1,0,0,102,9,1,0,0,0,103,108,3,30,15,0,104,105,5,41,0,0,
  	105,107,3,30,15,0,106,104,1,0,0,0,107,110,1,0,0,0,108,106,1,0,0,0,108,
  	109,1,0,0,0,109,11,1,0,0,0,110,108,1,0,0,0,111,116,3,14,7,0,112,113,7,
  	2,0,0,113,115,3,14,7,0,114,112,1,0,0,0,115,118,1,0,0,0,116,114,1,0,0,
  	0,116,117,1,0,0,0,117,13,1,0,0,0,118,116,1,0,0,0,119,124,3,6,3,0,120,
  	121,7,3,0,0,121,123,3,6,3,0,122,120,1,0,0,0,123,126,1,0,0,0,124,122,1,
  	0,0,0,124,125,1,0,0,0,125,15,1,0,0,0,126,124,1,0,0,0,127,130,3,12,6,0,
  	128,129,7,4,0,0,129,131,3,12,6,0,130,128,1,0,0,0,130,131,1,0,0,0,131,
  	17,1,0,0,0,132,135,3,16,8,0,133,134,7,5,0,0,134,136,3,16,8,0,135,133,
  	1,0,0,0,135,136,1,0,0,0,136,19,1,0,0,0,137,142,3,18,9,0,138,139,5,37,
  	0,0,139,141,3,18,9,0,140,138,1,0,0,0,141,144,1,0,0,0,142,140,1,0,0,0,
  	142,143,1,0,0,0,143,21,1,0,0,0,144,142,1,0,0,0,145,150,3,20,10,0,146,
  	147,5,38,0,0,147,149,3,20,10,0,148,146,1,0,0,0,149,152,1,0,0,0,150,148,
  	1,0,0,0,150,151,1,0,0,0,151,23,1,0,0,0,152,150,1,0,0,0,153,154,3,22,11,
  	0,154,25,1,0,0,0,155,158,3,72,36,0,156,158,5,7,0,0,157,155,1,0,0,0,157,
  	156,1,0,0,0,158,27,1,0,0,0,159,173,3,26,13,0,160,169,5,26,0,0,161,166,
  	3,28,14,0,162,163,5,41,0,0,163,165,3,28,14,0,164,162,1,0,0,0,165,168,
  	1,0,0,0,166,164,1,0,0,0,166,167,1,0,0,0,167,170,1,0,0,0,168,166,1,0,0,
  	0,169,161,1,0,0,0,169,170,1,0,0,0,170,171,1,0,0,0,171,173,5,27,0,0,172,
  	159,1,0,0,0,172,160,1,0,0,0,173,29,1,0,0,0,174,175,3,12,6,0,175,31,1,
  	0,0,0,176,179,3,34,17,0,177,179,3,38,19,0,178,176,1,0,0,0,178,177,1,0,
  	0,0,179,33,1,0,0,0,180,181,5,8,0,0,181,182,3,2,1,0,182,187,3,36,18,0,
  	183,184,5,41,0,0,184,186,3,36,18,0,185,183,1,0,0,0,186,189,1,0,0,0,187,
  	185,1,0,0,0,187,188,1,0,0,0,188,190,1,0,0,0,189,187,1,0,0,0,190,191,5,
  	40,0,0,191,35,1,0,0,0,192,198,5,46,0,0,193,194,5,24,0,0,194,195,5,5,0,
  	0,195,197,5,25,0,0,196,193,1,0,0,0,197,200,1,0,0,0,198,196,1,0,0,0,198,
  	199,1,0,0,0,199,201,1,0,0,0,200,198,1,0,0,0,201,202,5,42,0,0,202,203,
  	3,28,14,0,203,37,1,0,0,0,204,205,3,2,1,0,205,210,3,40,20,0,206,207,5,
  	41,0,0,207,209,3,40,20,0,208,206,1,0,0,0,209,212,1,0,0,0,210,208,1,0,
  	0,0,210,211,1,0,0,0,211,213,1,0,0,0,212,210,1,0,0,0,213,214,5,40,0,0,
  	214,39,1,0,0,0,215,221,5,46,0,0,216,217,5,24,0,0,217,218,5,5,0,0,218,
  	220,5,25,0,0,219,216,1,0,0,0,220,223,1,0,0,0,221,219,1,0,0,0,221,222,
  	1,0,0,0,222,226,1,0,0,0,223,221,1,0,0,0,224,225,5,42,0,0,225,227,3,28,
  	14,0,226,224,1,0,0,0,226,227,1,0,0,0,227,41,1,0,0,0,228,234,3,44,22,0,
  	229,234,3,46,23,0,230,234,3,48,24,0,231,234,3,50,25,0,232,234,3,52,26,
  	0,233,228,1,0,0,0,233,229,1,0,0,0,233,230,1,0,0,0,233,231,1,0,0,0,233,
  	232,1,0,0,0,234,43,1,0,0,0,235,237,5,26,0,0,236,238,3,56,28,0,237,236,
  	1,0,0,0,237,238,1,0,0,0,238,239,1,0,0,0,239,240,5,27,0,0,240,45,1,0,0,
  	0,241,243,3,30,15,0,242,241,1,0,0,0,242,243,1,0,0,0,243,244,1,0,0,0,244,
  	251,5,40,0,0,245,246,3,58,29,0,246,247,5,42,0,0,247,248,3,30,15,0,248,
  	249,5,40,0,0,249,251,1,0,0,0,250,242,1,0,0,0,250,245,1,0,0,0,251,47,1,
  	0,0,0,252,253,5,14,0,0,253,254,5,22,0,0,254,255,3,30,15,0,255,256,5,23,
  	0,0,256,259,3,42,21,0,257,258,5,15,0,0,258,260,3,42,21,0,259,257,1,0,
  	0,0,259,260,1,0,0,0,260,49,1,0,0,0,261,262,5,10,0,0,262,263,5,22,0,0,
  	263,264,3,30,15,0,264,265,5,23,0,0,265,266,3,42,21,0,266,51,1,0,0,0,267,
  	274,5,9,0,0,268,274,5,11,0,0,269,271,5,21,0,0,270,272,3,30,15,0,271,270,
  	1,0,0,0,271,272,1,0,0,0,272,274,1,0,0,0,273,267,1,0,0,0,273,268,1,0,0,
  	0,273,269,1,0,0,0,274,275,1,0,0,0,275,276,5,40,0,0,276,53,1,0,0,0,277,
  	280,3,42,21,0,278,280,3,32,16,0,279,277,1,0,0,0,279,278,1,0,0,0,280,55,
  	1,0,0,0,281,283,3,54,27,0,282,281,1,0,0,0,283,284,1,0,0,0,284,282,1,0,
  	0,0,284,285,1,0,0,0,285,57,1,0,0,0,286,293,5,46,0,0,287,288,5,24,0,0,
  	288,289,3,30,15,0,289,290,5,25,0,0,290,292,1,0,0,0,291,287,1,0,0,0,292,
  	295,1,0,0,0,293,291,1,0,0,0,293,294,1,0,0,0,294,59,1,0,0,0,295,293,1,
  	0,0,0,296,298,3,62,31,0,297,296,1,0,0,0,297,298,1,0,0,0,298,299,1,0,0,
  	0,299,300,5,0,0,1,300,61,1,0,0,0,301,303,3,64,32,0,302,301,1,0,0,0,303,
  	304,1,0,0,0,304,302,1,0,0,0,304,305,1,0,0,0,305,63,1,0,0,0,306,309,3,
  	66,33,0,307,309,3,32,16,0,308,306,1,0,0,0,308,307,1,0,0,0,309,65,1,0,
  	0,0,310,311,3,0,0,0,311,312,5,46,0,0,312,314,5,22,0,0,313,315,3,68,34,
  	0,314,313,1,0,0,0,314,315,1,0,0,0,315,316,1,0,0,0,316,317,5,23,0,0,317,
  	318,3,44,22,0,318,67,1,0,0,0,319,324,3,70,35,0,320,321,5,41,0,0,321,323,
  	3,70,35,0,322,320,1,0,0,0,323,326,1,0,0,0,324,322,1,0,0,0,324,325,1,0,
  	0,0,325,69,1,0,0,0,326,324,1,0,0,0,327,328,3,2,1,0,328,344,5,46,0,0,329,
  	331,5,24,0,0,330,332,5,5,0,0,331,330,1,0,0,0,331,332,1,0,0,0,332,333,
  	1,0,0,0,333,341,5,25,0,0,334,336,5,24,0,0,335,337,5,5,0,0,336,335,1,0,
  	0,0,336,337,1,0,0,0,337,338,1,0,0,0,338,340,5,25,0,0,339,334,1,0,0,0,
  	340,343,1,0,0,0,341,339,1,0,0,0,341,342,1,0,0,0,342,345,1,0,0,0,343,341,
  	1,0,0,0,344,329,1,0,0,0,344,345,1,0,0,0,345,71,1,0,0,0,346,347,7,6,0,
  	0,347,73,1,0,0,0,40,76,87,96,99,108,116,124,130,135,142,150,157,166,169,
  	172,178,187,198,210,221,226,233,237,242,250,259,271,273,279,284,293,297,
  	304,308,314,324,331,336,341,344
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
  enterRule(_localctx, 0, CACTParser::RuleFunctionType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(76);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::Void: {
        enterOuterAlt(_localctx, 1);
        setState(74);
        match(CACTParser::Void);
        break;
      }

      case CACTParser::Int:
      case CACTParser::Char:
      case CACTParser::Float:
      case CACTParser::Double: {
        enterOuterAlt(_localctx, 2);
        setState(75);
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

tree::TerminalNode* CACTParser::BasicTypeContext::Char() {
  return getToken(CACTParser::Char, 0);
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
  enterRule(_localctx, 2, CACTParser::RuleBasicType);
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
    setState(78);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1966080) != 0))) {
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

CACTParser::LeftValueContext* CACTParser::PrimaryExpressionContext::leftValue() {
  return getRuleContext<CACTParser::LeftValueContext>(0);
}

CACTParser::NumberContext* CACTParser::PrimaryExpressionContext::number() {
  return getRuleContext<CACTParser::NumberContext>(0);
}

tree::TerminalNode* CACTParser::PrimaryExpressionContext::CharacterConstant() {
  return getToken(CACTParser::CharacterConstant, 0);
}

tree::TerminalNode* CACTParser::PrimaryExpressionContext::LeftParenthesis() {
  return getToken(CACTParser::LeftParenthesis, 0);
}

CACTParser::ExpressionContext* CACTParser::PrimaryExpressionContext::expression() {
  return getRuleContext<CACTParser::ExpressionContext>(0);
}

tree::TerminalNode* CACTParser::PrimaryExpressionContext::RightParenthesis() {
  return getToken(CACTParser::RightParenthesis, 0);
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
  enterRule(_localctx, 4, CACTParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(87);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(80);
        leftValue();
        break;
      }

      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant: {
        enterOuterAlt(_localctx, 2);
        setState(81);
        number();
        break;
      }

      case CACTParser::CharacterConstant: {
        enterOuterAlt(_localctx, 3);
        setState(82);
        match(CACTParser::CharacterConstant);
        break;
      }

      case CACTParser::LeftParenthesis: {
        enterOuterAlt(_localctx, 4);
        setState(83);
        match(CACTParser::LeftParenthesis);
        setState(84);
        expression();
        setState(85);
        match(CACTParser::RightParenthesis);
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

tree::TerminalNode* CACTParser::UnaryExpressionContext::LeftParenthesis() {
  return getToken(CACTParser::LeftParenthesis, 0);
}

tree::TerminalNode* CACTParser::UnaryExpressionContext::RightParenthesis() {
  return getToken(CACTParser::RightParenthesis, 0);
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
  enterRule(_localctx, 6, CACTParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(99);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(89);
      primaryExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(90);
      unaryOperator();
      setState(91);
      unaryExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(93);
      match(CACTParser::Identifier);
      setState(94);
      match(CACTParser::LeftParenthesis);
      setState(96);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 70931389087968) != 0)) {
        setState(95);
        functionRParams();
      }
      setState(98);
      match(CACTParser::RightParenthesis);
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

//----------------- UnaryOperatorContext ------------------------------------------------------------------

CACTParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::UnaryOperatorContext::Plus() {
  return getToken(CACTParser::Plus, 0);
}

tree::TerminalNode* CACTParser::UnaryOperatorContext::Minus() {
  return getToken(CACTParser::Minus, 0);
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
  enterRule(_localctx, 8, CACTParser::RuleUnaryOperator);
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
    setState(101);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 562640715776) != 0))) {
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
    setState(103);
    expression();
    setState(108);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Comma) {
      setState(104);
      match(CACTParser::Comma);
      setState(105);
      expression();
      setState(110);
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

std::vector<tree::TerminalNode *> CACTParser::AdditiveExpressionContext::Plus() {
  return getTokens(CACTParser::Plus);
}

tree::TerminalNode* CACTParser::AdditiveExpressionContext::Plus(size_t i) {
  return getToken(CACTParser::Plus, i);
}

std::vector<tree::TerminalNode *> CACTParser::AdditiveExpressionContext::Minus() {
  return getTokens(CACTParser::Minus);
}

tree::TerminalNode* CACTParser::AdditiveExpressionContext::Minus(size_t i) {
  return getToken(CACTParser::Minus, i);
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
  enterRule(_localctx, 12, CACTParser::RuleAdditiveExpression);
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
    setState(111);
    multiplicativeExpression();
    setState(116);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Plus

    || _la == CACTParser::Minus) {
      setState(112);
      antlrcpp::downCast<AdditiveExpressionContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == CACTParser::Plus

      || _la == CACTParser::Minus)) {
        antlrcpp::downCast<AdditiveExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(113);
      multiplicativeExpression();
      setState(118);
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

std::vector<tree::TerminalNode *> CACTParser::MultiplicativeExpressionContext::Star() {
  return getTokens(CACTParser::Star);
}

tree::TerminalNode* CACTParser::MultiplicativeExpressionContext::Star(size_t i) {
  return getToken(CACTParser::Star, i);
}

std::vector<tree::TerminalNode *> CACTParser::MultiplicativeExpressionContext::Div() {
  return getTokens(CACTParser::Div);
}

tree::TerminalNode* CACTParser::MultiplicativeExpressionContext::Div(size_t i) {
  return getToken(CACTParser::Div, i);
}

std::vector<tree::TerminalNode *> CACTParser::MultiplicativeExpressionContext::Mod() {
  return getTokens(CACTParser::Mod);
}

tree::TerminalNode* CACTParser::MultiplicativeExpressionContext::Mod(size_t i) {
  return getToken(CACTParser::Mod, i);
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
  enterRule(_localctx, 14, CACTParser::RuleMultiplicativeExpression);
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
    unaryExpression();
    setState(124);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 120259084288) != 0)) {
      setState(120);
      antlrcpp::downCast<MultiplicativeExpressionContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120259084288) != 0))) {
        antlrcpp::downCast<MultiplicativeExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(121);
      unaryExpression();
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

tree::TerminalNode* CACTParser::RelationalExpressionContext::Less() {
  return getToken(CACTParser::Less, 0);
}

tree::TerminalNode* CACTParser::RelationalExpressionContext::Greater() {
  return getToken(CACTParser::Greater, 0);
}

tree::TerminalNode* CACTParser::RelationalExpressionContext::LessEqual() {
  return getToken(CACTParser::LessEqual, 0);
}

tree::TerminalNode* CACTParser::RelationalExpressionContext::GreaterEqual() {
  return getToken(CACTParser::GreaterEqual, 0);
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
  enterRule(_localctx, 16, CACTParser::RuleRelationalExpression);
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
    setState(127);
    additiveExpression();
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4026531840) != 0)) {
      setState(128);
      antlrcpp::downCast<RelationalExpressionContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4026531840) != 0))) {
        antlrcpp::downCast<RelationalExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(129);
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

tree::TerminalNode* CACTParser::EqualityExpressionContext::Equal() {
  return getToken(CACTParser::Equal, 0);
}

tree::TerminalNode* CACTParser::EqualityExpressionContext::NotEqual() {
  return getToken(CACTParser::NotEqual, 0);
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
  enterRule(_localctx, 18, CACTParser::RuleEqualityExpression);
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
    setState(132);
    relationalExpression();
    setState(135);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::Equal

    || _la == CACTParser::NotEqual) {
      setState(133);
      antlrcpp::downCast<EqualityExpressionContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == CACTParser::Equal

      || _la == CACTParser::NotEqual)) {
        antlrcpp::downCast<EqualityExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(134);
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

std::vector<tree::TerminalNode *> CACTParser::LogicalAndExpressionContext::AndAnd() {
  return getTokens(CACTParser::AndAnd);
}

tree::TerminalNode* CACTParser::LogicalAndExpressionContext::AndAnd(size_t i) {
  return getToken(CACTParser::AndAnd, i);
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
  enterRule(_localctx, 20, CACTParser::RuleLogicalAndExpression);
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
    setState(137);
    equalityExpression();
    setState(142);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::AndAnd) {
      setState(138);
      antlrcpp::downCast<LogicalAndExpressionContext *>(_localctx)->op = match(CACTParser::AndAnd);
      setState(139);
      equalityExpression();
      setState(144);
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

std::vector<tree::TerminalNode *> CACTParser::LogicalOrExpressionContext::OrOr() {
  return getTokens(CACTParser::OrOr);
}

tree::TerminalNode* CACTParser::LogicalOrExpressionContext::OrOr(size_t i) {
  return getToken(CACTParser::OrOr, i);
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
  enterRule(_localctx, 22, CACTParser::RuleLogicalOrExpression);
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
    setState(145);
    logicalAndExpression();
    setState(150);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::OrOr) {
      setState(146);
      antlrcpp::downCast<LogicalOrExpressionContext *>(_localctx)->op = match(CACTParser::OrOr);
      setState(147);
      logicalAndExpression();
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
  enterRule(_localctx, 24, CACTParser::RuleCondition);

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
    logicalOrExpression();
   
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

tree::TerminalNode* CACTParser::ConstantExpressionContext::CharacterConstant() {
  return getToken(CACTParser::CharacterConstant, 0);
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
  enterRule(_localctx, 26, CACTParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(157);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant: {
        enterOuterAlt(_localctx, 1);
        setState(155);
        number();
        break;
      }

      case CACTParser::CharacterConstant: {
        enterOuterAlt(_localctx, 2);
        setState(156);
        match(CACTParser::CharacterConstant);
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
  enterRule(_localctx, 28, CACTParser::RuleConstantInitValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(172);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant:
      case CACTParser::CharacterConstant: {
        enterOuterAlt(_localctx, 1);
        setState(159);
        constantExpression();
        break;
      }

      case CACTParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(160);
        match(CACTParser::LeftBrace);
        setState(169);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 67109088) != 0)) {
          setState(161);
          constantInitValue();
          setState(166);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == CACTParser::Comma) {
            setState(162);
            match(CACTParser::Comma);
            setState(163);
            constantInitValue();
            setState(168);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(171);
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

//----------------- ExpressionContext ------------------------------------------------------------------

CACTParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::AdditiveExpressionContext* CACTParser::ExpressionContext::additiveExpression() {
  return getRuleContext<CACTParser::AdditiveExpressionContext>(0);
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
  enterRule(_localctx, 30, CACTParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(174);
    additiveExpression();
   
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
  enterRule(_localctx, 32, CACTParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(178);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::Const: {
        enterOuterAlt(_localctx, 1);
        setState(176);
        constantDeclaration();
        break;
      }

      case CACTParser::Int:
      case CACTParser::Char:
      case CACTParser::Float:
      case CACTParser::Double: {
        enterOuterAlt(_localctx, 2);
        setState(177);
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

tree::TerminalNode* CACTParser::ConstantDeclarationContext::Semicolon() {
  return getToken(CACTParser::Semicolon, 0);
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
  enterRule(_localctx, 34, CACTParser::RuleConstantDeclaration);
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
    setState(180);
    match(CACTParser::Const);
    setState(181);
    basicType();
    setState(182);
    constantDefinition();
    setState(187);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Comma) {
      setState(183);
      match(CACTParser::Comma);
      setState(184);
      constantDefinition();
      setState(189);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(190);
    match(CACTParser::Semicolon);
   
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
  enterRule(_localctx, 36, CACTParser::RuleConstantDefinition);
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
    setState(192);
    match(CACTParser::Identifier);
    setState(198);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::LeftBracket) {
      setState(193);
      match(CACTParser::LeftBracket);
      setState(194);
      match(CACTParser::IntegerConstant);
      setState(195);
      match(CACTParser::RightBracket);
      setState(200);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(201);
    match(CACTParser::Assign);
    setState(202);
    constantInitValue();
   
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

tree::TerminalNode* CACTParser::VariableDeclarationContext::Semicolon() {
  return getToken(CACTParser::Semicolon, 0);
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
  enterRule(_localctx, 38, CACTParser::RuleVariableDeclaration);
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
    setState(204);
    basicType();
    setState(205);
    variableDefinition();
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Comma) {
      setState(206);
      match(CACTParser::Comma);
      setState(207);
      variableDefinition();
      setState(212);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(213);
    match(CACTParser::Semicolon);
   
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
  enterRule(_localctx, 40, CACTParser::RuleVariableDefinition);
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
    setState(215);
    match(CACTParser::Identifier);
    setState(221);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::LeftBracket) {
      setState(216);
      match(CACTParser::LeftBracket);
      setState(217);
      match(CACTParser::IntegerConstant);
      setState(218);
      match(CACTParser::RightBracket);
      setState(223);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::Assign) {
      setState(224);
      match(CACTParser::Assign);
      setState(225);
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
  enterRule(_localctx, 42, CACTParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(233);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::LeftBrace: {
        enterOuterAlt(_localctx, 1);
        setState(228);
        compoundStatement();
        break;
      }

      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant:
      case CACTParser::CharacterConstant:
      case CACTParser::LeftParenthesis:
      case CACTParser::Plus:
      case CACTParser::Minus:
      case CACTParser::Not:
      case CACTParser::Semicolon:
      case CACTParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(229);
        expressionStatement();
        break;
      }

      case CACTParser::If: {
        enterOuterAlt(_localctx, 3);
        setState(230);
        selectionStatement();
        break;
      }

      case CACTParser::While: {
        enterOuterAlt(_localctx, 4);
        setState(231);
        iterationStatement();
        break;
      }

      case CACTParser::Continue:
      case CACTParser::Break:
      case CACTParser::Return: {
        enterOuterAlt(_localctx, 5);
        setState(232);
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
  enterRule(_localctx, 44, CACTParser::RuleCompoundStatement);
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
    setState(235);
    match(CACTParser::LeftBrace);
    setState(237);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72030971908064) != 0)) {
      setState(236);
      blockItemList();
    }
    setState(239);
    match(CACTParser::RightBrace);
   
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

tree::TerminalNode* CACTParser::ExpressionStatementContext::Semicolon() {
  return getToken(CACTParser::Semicolon, 0);
}

CACTParser::ExpressionContext* CACTParser::ExpressionStatementContext::expression() {
  return getRuleContext<CACTParser::ExpressionContext>(0);
}

CACTParser::LeftValueContext* CACTParser::ExpressionStatementContext::leftValue() {
  return getRuleContext<CACTParser::LeftValueContext>(0);
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
  enterRule(_localctx, 46, CACTParser::RuleExpressionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(250);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(242);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 70931389087968) != 0)) {
        setState(241);
        expression();
      }
      setState(244);
      match(CACTParser::Semicolon);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(245);
      leftValue();
      setState(246);
      match(CACTParser::Assign);
      setState(247);
      expression();
      setState(248);
      match(CACTParser::Semicolon);
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

//----------------- SelectionStatementContext ------------------------------------------------------------------

CACTParser::SelectionStatementContext::SelectionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::SelectionStatementContext::If() {
  return getToken(CACTParser::If, 0);
}

tree::TerminalNode* CACTParser::SelectionStatementContext::LeftParenthesis() {
  return getToken(CACTParser::LeftParenthesis, 0);
}

CACTParser::ExpressionContext* CACTParser::SelectionStatementContext::expression() {
  return getRuleContext<CACTParser::ExpressionContext>(0);
}

tree::TerminalNode* CACTParser::SelectionStatementContext::RightParenthesis() {
  return getToken(CACTParser::RightParenthesis, 0);
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
  enterRule(_localctx, 48, CACTParser::RuleSelectionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    match(CACTParser::If);
    setState(253);
    match(CACTParser::LeftParenthesis);
    setState(254);
    expression();
    setState(255);
    match(CACTParser::RightParenthesis);
    setState(256);
    statement();
    setState(259);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(257);
      match(CACTParser::Else);
      setState(258);
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

tree::TerminalNode* CACTParser::IterationStatementContext::LeftParenthesis() {
  return getToken(CACTParser::LeftParenthesis, 0);
}

CACTParser::ExpressionContext* CACTParser::IterationStatementContext::expression() {
  return getRuleContext<CACTParser::ExpressionContext>(0);
}

tree::TerminalNode* CACTParser::IterationStatementContext::RightParenthesis() {
  return getToken(CACTParser::RightParenthesis, 0);
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
  enterRule(_localctx, 50, CACTParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(261);
    match(CACTParser::While);
    setState(262);
    match(CACTParser::LeftParenthesis);
    setState(263);
    expression();
    setState(264);
    match(CACTParser::RightParenthesis);
    setState(265);
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

tree::TerminalNode* CACTParser::JumpStatementContext::Semicolon() {
  return getToken(CACTParser::Semicolon, 0);
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
  enterRule(_localctx, 52, CACTParser::RuleJumpStatement);
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
    setState(273);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::Continue: {
        setState(267);
        match(CACTParser::Continue);
        break;
      }

      case CACTParser::Break: {
        setState(268);
        match(CACTParser::Break);
        break;
      }

      case CACTParser::Return: {
        setState(269);
        match(CACTParser::Return);
        setState(271);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 70931389087968) != 0)) {
          setState(270);
          expression();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(275);
    match(CACTParser::Semicolon);
   
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
  enterRule(_localctx, 54, CACTParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(279);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntegerConstant:
      case CACTParser::FloatingConstant:
      case CACTParser::CharacterConstant:
      case CACTParser::Continue:
      case CACTParser::While:
      case CACTParser::Break:
      case CACTParser::If:
      case CACTParser::Return:
      case CACTParser::LeftParenthesis:
      case CACTParser::LeftBrace:
      case CACTParser::Plus:
      case CACTParser::Minus:
      case CACTParser::Not:
      case CACTParser::Semicolon:
      case CACTParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(277);
        statement();
        break;
      }

      case CACTParser::Const:
      case CACTParser::Int:
      case CACTParser::Char:
      case CACTParser::Float:
      case CACTParser::Double: {
        enterOuterAlt(_localctx, 2);
        setState(278);
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
  enterRule(_localctx, 56, CACTParser::RuleBlockItemList);
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
    setState(282); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(281);
      blockItem();
      setState(284); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72030971908064) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LeftValueContext ------------------------------------------------------------------

CACTParser::LeftValueContext::LeftValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::LeftValueContext::Identifier() {
  return getToken(CACTParser::Identifier, 0);
}

std::vector<tree::TerminalNode *> CACTParser::LeftValueContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::LeftValueContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<CACTParser::ExpressionContext *> CACTParser::LeftValueContext::expression() {
  return getRuleContexts<CACTParser::ExpressionContext>();
}

CACTParser::ExpressionContext* CACTParser::LeftValueContext::expression(size_t i) {
  return getRuleContext<CACTParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::LeftValueContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::LeftValueContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
}


size_t CACTParser::LeftValueContext::getRuleIndex() const {
  return CACTParser::RuleLeftValue;
}


std::any CACTParser::LeftValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitLeftValue(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::LeftValueContext* CACTParser::leftValue() {
  LeftValueContext *_localctx = _tracker.createInstance<LeftValueContext>(_ctx, getState());
  enterRule(_localctx, 58, CACTParser::RuleLeftValue);
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
    setState(286);
    match(CACTParser::Identifier);
    setState(293);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::LeftBracket) {
      setState(287);
      match(CACTParser::LeftBracket);
      setState(288);
      expression();
      setState(289);
      match(CACTParser::RightBracket);
      setState(295);
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
  enterRule(_localctx, 60, CACTParser::RuleCompilationUnit);
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
    setState(297);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2031872) != 0)) {
      setState(296);
      translationUnit();
    }
    setState(299);
    match(CACTParser::EOF);
   
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
  enterRule(_localctx, 62, CACTParser::RuleTranslationUnit);
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
    setState(302); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(301);
      externalDeclaration();
      setState(304); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2031872) != 0));
   
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
  enterRule(_localctx, 64, CACTParser::RuleExternalDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(308);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(306);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(307);
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

tree::TerminalNode* CACTParser::FunctionDefinitionContext::LeftParenthesis() {
  return getToken(CACTParser::LeftParenthesis, 0);
}

tree::TerminalNode* CACTParser::FunctionDefinitionContext::RightParenthesis() {
  return getToken(CACTParser::RightParenthesis, 0);
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
  enterRule(_localctx, 66, CACTParser::RuleFunctionDefinition);
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
    setState(310);
    functionType();
    setState(311);
    match(CACTParser::Identifier);
    setState(312);
    match(CACTParser::LeftParenthesis);
    setState(314);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1966080) != 0)) {
      setState(313);
      functionFParams();
    }
    setState(316);
    match(CACTParser::RightParenthesis);
    setState(317);
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
  enterRule(_localctx, 68, CACTParser::RuleFunctionFParams);
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
    setState(319);
    functionFParam();
    setState(324);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::Comma) {
      setState(320);
      match(CACTParser::Comma);
      setState(321);
      functionFParam();
      setState(326);
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
  enterRule(_localctx, 70, CACTParser::RuleFunctionFParam);
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
    setState(327);
    basicType();
    setState(328);
    match(CACTParser::Identifier);
    setState(344);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::LeftBracket) {
      setState(329);
      match(CACTParser::LeftBracket);
      setState(331);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CACTParser::IntegerConstant) {
        setState(330);
        match(CACTParser::IntegerConstant);
      }
      setState(333);
      match(CACTParser::RightBracket);
      setState(341);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CACTParser::LeftBracket) {
        setState(334);
        match(CACTParser::LeftBracket);
        setState(336);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CACTParser::IntegerConstant) {
          setState(335);
          match(CACTParser::IntegerConstant);
        }
        setState(338);
        match(CACTParser::RightBracket);
        setState(343);
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

tree::TerminalNode* CACTParser::NumberContext::IntegerConstant() {
  return getToken(CACTParser::IntegerConstant, 0);
}

tree::TerminalNode* CACTParser::NumberContext::FloatingConstant() {
  return getToken(CACTParser::FloatingConstant, 0);
}


size_t CACTParser::NumberContext::getRuleIndex() const {
  return CACTParser::RuleNumber;
}


std::any CACTParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::NumberContext* CACTParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 72, CACTParser::RuleNumber);
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
    setState(346);
    _la = _input->LA(1);
    if (!(_la == CACTParser::IntegerConstant

    || _la == CACTParser::FloatingConstant)) {
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

void CACTParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  cactParserInitialize();
#else
  ::antlr4::internal::call_once(cactParserOnceFlag, cactParserInitialize);
#endif
}

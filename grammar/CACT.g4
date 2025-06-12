grammar CACT;

@header {
    #include <vector>
    #include <string>
    #include "utils/CACT.h"
    #include "symbolTable.h"
    #include "IR/IRBasicBlock.h"
}

/****** parser ******/

compilationUnit
    : translationUnit? EOF
    ;

functionType
    : 'void'
    | basicType
    ;

basicType
    : 'int'
    | 'bool'
    | 'float'
    | 'double'
    ;

primaryExpression
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : lValue
    | number 
    | LeftParen expression RightParen
    ;

unaryExpression
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : primaryExpression
    | unaryOperator unaryExpression
    | Identifier LeftParen (functionRParams)? RightParen
    ;

functionRParams
    locals [FuncSymbolInfo *func]
    : expression (',' expression)*
    ;

unaryOperator
    : addOp
    | Not
    ;

addOp
    : '+'
    | '-'
    ;

/*以下优先级是往下递减的，A->B op B，则B的优先级比A的优先级要高 */
//unaryExpression的优先级比较高
multiplicativeExpression
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : unaryExpression (multiplicativeOp unaryExpression)*
    ;

multiplicativeOp
    : '*'
    | '/'
    | '%'
    ;

additiveExpression
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : multiplicativeExpression (additiveOp multiplicativeExpression)*
    ;

additiveOp
    : '+'
    | '-'
    ;

relationalExpression
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : additiveExpression (relationalOp additiveExpression)?
    ;

relationalOp
    : '<'
    | '>'
    | '<='
    | '>='
    ;

equalityExpression
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : relationalExpression (equalityOp relationalExpression)?
    ;

equalityOp
    : '=='
    | '!='
    ;

logicalAndExpression
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : equalityExpression (logicalAndOp equalityExpression)*
    ;

logicalAndOp
    : '&&'
    ;

logicalOrExpression
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : logicalAndExpression (logicalOrOp logicalAndExpression)*
    ;

logicalOrOp
    : '||'
    ;

/*****************************以上*****************************/

expression
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : additiveExpression
    | BooleanConstant
    ;
//expression是最基础的表达式

constantExpression
    locals [DataType dataType]
    : (addOp)? number
    | BooleanConstant
    ;

condition
    locals [IRBasicBlock *trueBlock = nullptr,
            IRBasicBlock *falseBlock = nullptr]
    : logicalOrExpression
    ;


/*declaration部分 */
declaration
    //locals [BlockInfo * thisblockinfo]
    : constantDeclaration
    | variableDeclaration
    ;

constantDeclaration
    locals [DataType dataType]
    : Const basicType constantDefinition (',' constantDefinition)* ';'
    ;

constantDefinition
    locals [DataType dataType,
            std::vector<int> arraySize]
    : Identifier (LeftBracket IntegerConstant RightBracket)* Assign constantInitValue
    ;

constantInitValue
    locals [DataType dataType,
            std::vector<int> arraySize,
            int dimension]
    : constantExpression
    | LeftBrace (constantInitValue (',' constantInitValue)*)? RightBrace//这里可能考虑的是对数组进行赋值
    ;                                                                           

variableDeclaration
    locals [DataType dataType]
    : basicType variableDefinition (',' variableDefinition)* ';'
    ;

variableDefinition
    locals [DataType dataType,
            std::vector<int> arraySize]
    : Identifier (LeftBracket IntegerConstant RightBracket)* (Assign constantInitValue)?
    ;
/*declaration部分 */
/*CACT中声明的时候对于const必须显式的进行赋值 */

statement
    : compoundStatement
    | expressionStatement
    | selectionStatement
    | iterationStatement
    | jumpStatement
    ;

compoundStatement//复合语句
    locals [BlockInfo * thisblockinfo,
            FuncSymbolInfo * thisfuncinfo = nullptr]
    : LeftBrace blockItemList? RightBrace
    ;

blockItemList
    //locals [BlockItemContext * lastblockitem]
    : blockItem+
    ;

blockItem
    : statement//往下添加子块
    | declaration//往下添加符号表
    ;
//一个blockItem要么是一个语句，要么是一个声明

expressionStatement
    : expression? ';' // 函数调用
    | lValue Assign expression ';'
    ;
//表达式语句

lValue
    locals [bool loadable]
    : Identifier (LeftBracket expression RightBracket)*
    ;
//lvalue一般是针对数组

selectionStatement
    locals [BlockInfo * thisblockinfo,
            bool ifelseType = false]
    : If LeftParen condition RightParen statement (Else statement)?
    ;
//暂且不考虑else if

iterationStatement
    locals [BlockInfo * thisblockinfo,
            IRBasicBlock *preheader = nullptr,
            IRBasicBlock *bodyBlock = nullptr,
            IRBasicBlock *latch = nullptr,
            IRBasicBlock *nextBlock = nullptr]
    : While LeftParen condition RightParen statement
    ;
//暂且不考虑for循环

jumpStatement
    : (
        Continue
        | Break
        | Return expression?
    ) ';'
    ;
//jump

translationUnit
    : externalDeclaration+
    ;

externalDeclaration
    //locals [BlockInfo * thisblockinfo]
    : functionDefinition
    | declaration
    ;

functionDefinition
    locals [BlockInfo * thisblockinfo ,
            FuncSymbolInfo * thisfuncinfo]
    : functionType Identifier LeftParen functionFParams? RightParen compoundStatement
    ;

functionFParams
    locals [FuncSymbolInfo * thisfuncinfo,
            std::vector < SymbolInfo * > paramList,
            IRBasicBlock* irbasicblock]
    : functionFParam (',' functionFParam)*
    ;

functionFParam
    locals [FuncSymbolInfo * thisfuncinfo,
            SymbolInfo * Fparam,
            unsigned beforeFuncCount,
            IRBasicBlock* irbasicblock]
    : basicType Identifier (LeftBracket IntegerConstant? RightBracket (LeftBracket IntegerConstant? RightBracket)*)?
    ;

number
    : IntegerConstant   # IntegerConstant
    | FloatingConstant  # FloatingConstant
    ;

/****** lexer  ******/

IntegerConstant
    : DecimalConstant
    | OctalConstant
    | HexadecimalConstant
    ;

FloatingConstant
    : FractionalConstant ExponentPart? FloatingSuffix?
    | DigitSequence ExponentPart FloatingSuffix?
    ;

BooleanConstant
    : True
    | False
    ;

Bool
    : 'bool'
    ;

Break
    : 'break'
    ;

Const
    : 'const'
    ;

Continue
    : 'continue'
    ;

Double
    : 'double'
    ;

Else
    : 'else'
    ;

False
    : 'false'
    ;

Float
    : 'float'
    ;

If
    : 'if'
    ;

Int
    : 'int'
    ;

Return
    : 'return'
    ;

True
    : 'true'
    ;

Void
    : 'void'
    ;

While
    : 'while'
    ;

LeftParen
    : '('
    ;

RightParen
    : ')'
    ;

LeftBracket
    : '['
    ;

RightBracket
    : ']'
    ;

LeftBrace
    : '{'
    ;

RightBrace
    : '}'
    ;

Less
    : '<'
    ;

LessEqual
    : '<='
    ;

Greater
    : '>'
    ;

GreaterEqual
    : '>='
    ;

Plus
    : '+'
    ;

Minus
    : '-'
    ;

Star
    : '*'
    ;

Div
    : '/'
    ;

Mod
    : '%'
    ;

AndAnd
    : '&&'
    ;

OrOr
    : '||'
    ;

Not
    : '!'
    ;

Semi
    : ';'
    ;

Comma
    : ','
    ;

Assign
    : '='
    ;

Equal
    : '=='
    ;

NotEqual
    : '!='
    ;

Dot
    : '.'
    ;

Identifier
    : Nondigit (Nondigit | Digit)*
    ;

fragment Nondigit
    : [a-zA-Z_]
    ;

fragment Digit
    : [0-9]
    ;

fragment DecimalConstant
    : NonzeroDigit Digit*
    ;

fragment OctalConstant
    : '0' OctalDigit*
    ;

fragment HexadecimalConstant
    : HexadecimalPrefix HexadecimalDigit+
    ;

fragment HexadecimalPrefix
    : '0' [xX]
    ;

fragment NonzeroDigit
    : [1-9]
    ;

fragment OctalDigit
    : [0-7]
    ;

fragment HexadecimalDigit
    : [0-9a-fA-F]
    ;

fragment FractionalConstant
    : DigitSequence? '.' DigitSequence
    | DigitSequence '.'
    ;

fragment ExponentPart
    : [eE] Sign? DigitSequence
    ;

fragment Sign
    : [+-]
    ;

fragment DigitSequence
    : Digit+
    ;

fragment FloatingSuffix
    : [fF]
    ;

/****** skips  ******/
Whitespace
    : [ \t]+ -> channel(HIDDEN)
    ;

Newline
    : ('\r' '\n'? | '\n') -> channel(HIDDEN)
    ;

BlockComment
    : '/*' .*? '*/' -> channel(HIDDEN)
    ;

LineComment
    : '//' ~[\r\n]* -> channel(HIDDEN)
    ;

grammar CACT;

@header {
    #include <vector>
    #include <string>
}

/* parser */

functionType
    : 'void'
    | basicType
    ;

basicType
    : 'int'
    | 'char'
    | 'float'
    | 'double'
    ;

primaryExpression
    : leftValue
    | number 
    | CharacterConstant
    | '(' expression ')'
    ;

unaryExpression
    : primaryExpression
    | unaryOperator unaryExpression
    | Identifier '(' (functionRParams)? ')'
    ;

unaryOperator
    : '+'
    | '-'
    | '!'
    ;

functionRParams
    : expression (',' expression)*
    ;

additiveExpression
    : multiplicativeExpression (op = ('+' | '-') multiplicativeExpression)*
    ;

multiplicativeExpression
    : unaryExpression (op = ('*' | '/' | '%') unaryExpression)*
    ;

relationalExpression
    : additiveExpression (op = ('<' | '>' | '<=' | '>=') additiveExpression)?
    ;

equalityExpression
    : relationalExpression (op = ('==' | '!=') relationalExpression)?
    ;

logicalAndExpression
    : equalityExpression (op = '&&' equalityExpression)*
    ;

logicalOrExpression
    : logicalAndExpression (op = '||' logicalAndExpression)*
    ;

condition
    : logicalOrExpression
    ;

constantExpression
    : number
    | CharacterConstant
    ;

constantInitValue
    : constantExpression
    | '{' (constantInitValue (',' constantInitValue)*)? '}'
    ;

expression
    : additiveExpression 
    ;

declaration
    : constantDeclaration
    | variableDeclaration
    ;

constantDeclaration
    : 'const' basicType constantDefinition (',' constantDefinition)* ';'
    ;

constantDefinition
    : Identifier ('[' IntegerConstant ']')* '=' constantInitValue
    ;

variableDeclaration
    : basicType variableDefinition (',' variableDefinition)* ';'
    ;

variableDefinition
    : Identifier ('[' IntegerConstant ']')* ('=' constantInitValue)?
    ;

statement
    : compoundStatement
    | expressionStatement
    | selectionStatement
    | iterationStatement
    | jumpStatement
    ;

compoundStatement
    : '{' blockItemList? '}'
    ;

expressionStatement
    : expression? ';'
    | leftValue '=' expression ';'
    ;

selectionStatement
    : If '(' expression ')' statement (Else statement)?
    ;

iterationStatement
    : While '(' expression ')' statement
    ;

jumpStatement
    : (
        Continue
        | Break
        | Return expression?
    ) ';'
    ;

blockItem
    : statement
    | declaration
    ;

blockItemList
    : blockItem+
    ;

leftValue
    : Identifier ('[' expression ']')* 
    ;

compilationUnit
    : translationUnit? EOF
    ;

translationUnit
    : externalDeclaration+
    ;

externalDeclaration
    : functionDefinition
    | declaration
    ;

functionDefinition
    : functionType Identifier '(' functionFParams? ')' compoundStatement
    ;

functionFParams
    : functionFParam (',' functionFParam)*
    ;

functionFParam
    : basicType Identifier ('[' IntegerConstant? ']' ('[' IntegerConstant? ']')*)?
    ;

number
    : IntegerConstant
    | FloatingConstant
    ;

/* -skip- */

Whitespace
    : [ \t]+ -> channel(HIDDEN)
    ;

Newline
    : ('\r' '\n'? | '\n') -> channel(HIDDEN)
    ;

CommentLine
    : '//' ~[\r\n]* -> channel(HIDDEN)
    ;

CommentBlock
    : '/*' .*? '*/' -> channel(HIDDEN)
    ;

/* lexer */

IntegerConstant
    : DecimalConstant
    | OctalConstant
    | HexadecimalConstant
    ;

FloatingConstant
    : FractionalConstant ExponentPart? FloatingSuffix?
    | DigitSequence ExponentPart FloatingSuffix?
    ;

CharacterConstant
    : '\'' (EscapeSequence | ~['\\\r\n]) '\''
    ;

fragment EscapeSequence
    : '\\' [btnvrfa\\'"?]
    | '\\' OctalDigit+
    | '\\x' HexadecimalDigit+
    ;

Const
    : 'const'
    ;

Continue
    : 'continue'
    ;

While
    : 'while'
    ;

Break
    : 'break'
    ;

True
    : 'true'
    ;

False
    : 'false'
    ;

If
    : 'if'
    ;

Else
    : 'else'
    ;

Void
    : 'void'
    ;

Int
    : 'int'
    ;

Char
    : 'char'
    ;

Float
    : 'float'
    ;

Double
    : 'double'
    ;

Return
    : 'return'
    ;

LeftParenthesis
    : '('
    ;

RightParenthesis
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

Semicolon
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

fragment Digit
    : [0-9]
    ;

fragment Nondigit
    : [a-zA-Z_]
    ;

fragment OctalConstant
    : '0' OctalDigit*
    ;

fragment OctalDigit
    : [0-7]
    ;

fragment HexadecimalConstant
    : HexadecimalPrefix HexadecimalDigit+
    ;

fragment HexadecimalPrefix
    : '0' [xX]
    ;

fragment HexadecimalDigit
    : [0-9a-fA-F]
    ;

fragment DecimalConstant
    : NonzeroDigit Digit*
    ;

fragment NonzeroDigit
    : [1-9]
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
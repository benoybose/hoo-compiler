// Terminals.g4

grammar Terminals;

BasicDataType
    : ('int' | 'char' | 'string' | 'bool' | 'byte' | 'double')
    ;

ByteLiteral
    : HexadecimalPrefix HexadecimalDigit HexadecimalDigit
    ;

fragment UniversalCharacterName
    :   '\\u' HexQuad
    |   '\\U' HexQuad HexQuad
    ;

fragment HexQuad
    :   HexadecimalDigit HexadecimalDigit HexadecimalDigit HexadecimalDigit
    ;

IntegerLiteral
    :   DecimalConstant
    |   OctalConstant
    |   HexadecimalConstant
    |   BinaryConstant
    ;

fragment BinaryConstant
    :   '0' [bB] [0-1]+
    ;

fragment DecimalConstant
    :   Sign? NonzeroDigit Digit*
    ;

fragment OctalConstant
    :   '0' OctalDigit*
    ;

fragment HexadecimalConstant
    :   HexadecimalPrefix HexadecimalDigit+
    ;

fragment HexadecimalPrefix
    :   '0' [xX]
    ;

fragment NonzeroDigit
    :   [1-9]
    ;

fragment OctalDigit
    :   [0-7]
    ;

fragment HexadecimalDigit
    :   [0-9a-fA-F]
    ;

DoubleLiteral
    :   DecimalFloatingConstant
    ;

fragment DecimalFloatingConstant
    :   Sign? FractionalConstant ExponentPart?
    |   Sign? DigitSequence ExponentPart
    ;

fragment FractionalConstant
    :   DigitSequence? '.' DigitSequence
    |   DigitSequence '.'
    ;

fragment ExponentPart
    :   'e' Sign? DigitSequence
    |   'E' Sign? DigitSequence
    ;

fragment Sign
    :   '+' | '-'
    ;

DigitSequence
    :   Digit+
    ;

fragment HexadecimalDigitSequence
    :   HexadecimalDigit+
    ;

CharLiteral
    :   '\'' CCharSequence '\''
    ;

fragment CCharSequence
    :   CChar+
    ;

fragment CChar
    :   ~['\\\r\n]
    |   EscapeSequence
    ;

fragment EscapeSequence
    :   SimpleEscapeSequence
    |   OctalEscapeSequence
    |   HexadecimalEscapeSequence
    |   UniversalCharacterName
    ;

fragment SimpleEscapeSequence
    :   '\\' ['"?abfnrtv\\]
    ;

fragment OctalEscapeSequence
    :   '\\' OctalDigit
    |   '\\' OctalDigit OctalDigit
    |   '\\' OctalDigit OctalDigit OctalDigit
    ;

fragment HexadecimalEscapeSequence
    :   '\\x' HexadecimalDigit+
    ;

StringLiteral
    :   '"' SCharSequence? '"'
    ;

fragment SCharSequence
    :   SChar+
    ;

fragment SChar
    :   ~["\\\r\n]
    |   EscapeSequence
    |   '\\\n'   // Added line
    |   '\\\r\n' // Added line
    ;

BooleanLiteral
    : 'true' | 'false'
    ;

Identifier
    :   IdentifierNondigit
        (   IdentifierNondigit
        |   Digit
        )*
    ;

fragment IdentifierNondigit
    :   Nondigit
    |   UniversalCharacterName
    ;

fragment Nondigit
    :   [a-zA-Z_]
    ;

fragment Digit
    :   [0-9]
    ;

Whitespace
    :   [ \t]+
        -> skip
    ;

Newline
    :   (   '\r' '\n'?
        |   '\n'
        )
        -> skip
    ;

BlockComment
    :   '/*' .*? '*/'
        -> skip
    ;

LineComment
    :   '//' ~[\r\n]*
        -> skip
    ;

ExtraSymbolCharacters: ( '#' | '@' | '$' | '`' | '?' )
    ;

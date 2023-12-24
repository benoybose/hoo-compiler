// Hoo.g4

grammar Hoo;

import Terminals;

options {
    language=Cpp;
}

literalExpression
    :   ByteLiteral
    |   IntegerLiteral
    |   DoubleLiteral
    |   CharLiteral
    |   BooleanLiteral
    ;

stringExpression
    : StringLiteral
    ;

identifierExpression
    : Identifier
    ;

primaryExpression
    :   literalExpression
    |   stringExpression
    |   identifierExpression
    ;

expression
    :   primaryExpression #simpleExpression
    |   container=expression '[' accessIndex=expression ']' #arrayAccessExpression
    |   receiver=expression '(' arguments=expressionList? ')' #invokeExpression
    |   parent=expression '.' name=Identifier #nestedExpression
    |   lvalue=expression opr=('|' | '&' | '^' | '~' | '<<' | '>>') rvalue=expression #binaryBitExpression
    |   lvalue=expression opr=( '+' | '-' ) rvalue=expression #binaryAddExpression
    |   lvalue=expression opr=( '*' | '/' | '%') rvalue=expression #binaryMultiplicateExpression
    |   lvalue=expression opr=( '==' | '!=' | '>' | '<' | '>=' | '<=' ) rvalue=expression #binaryCompareExpression
    |   lvalue=expression opr=( '&&' | '||' ) rvalue=expression #binaryLogicExpression
    |   lvalue=expression opr=( '=' | '+=' | '-=' | '/=' | '*=' ) rvalue=expression #binaryAssignmentExpression
    |   '(' expression ')' #groupedExpression
    |   '(' typeSpecifier  expression ')' #castExpression
    ;

typeSpecifier
    :   BasicDataType #basicDataTypeSpecifier
    |   Identifier  #identifierTypeSpecifier
    |   typeSpecifier '.' Identifier #nestedTypeSpecifier
    |   typeSpecifier '[' ']' #arrayTypeSpecifier
    ;

expressionList
    :
    expression ( ',' expression )*
    ;

statement
    :   declarationStatement
    |   operativeStatement
    |   noOpStatement
    ;

noOpStatement
    : ';'
    ;

operativeStatement
    :   compoundStatement
    |   returnStatement
    |   expressionStatement
    ;

expressionStatement
    :   expression ';'
    ;

declarationStatement
    :   variableDeclaration ';'
    |   functionDeclaration ';'
    ;

compoundStatement
    : '{' statement* '}'
    ;

returnStatement
    :   'return' (returnValue=expression)? ';'
    ;

classDefinition
    :   'class' className=Identifier ( ':' baseEntities=typeList  )? classBody
    ;

typeList
    : typeSpecifier ( ',' typeSpecifier)*
    ;

classBody
    :
        '{'
            classBodyItem*
        '}'
    ;

classBodyItem
    :   defenition
    |   declarationStatement
    ;

functionDefinition
    :   functionDeclaration function_body=operativeStatement
    ;

functionDeclaration
    :   Declarator? name=Identifier '(' paramList? ')' ( ':' returnType=typeSpecifier)?
    ;

variableDeclaration
    :   type=( 'let' | 'const' ) decl=storageItem
    ;

storageItem
    :   typedStorageItem
    |   name=Identifier '=' init=primaryExpression
    ;

typedStorageItem
    :   name=Identifier ':' declared_type=typeSpecifier
    |   name=Identifier ':' declared_type=typeSpecifier '=' init=expression
    ;

paramList
    : typedStorageItem ( ',' typedStorageItem)+
    ;

Declarator
    :   'private' | 'public' | 'protected' | 'var'
    ;

defenition
    :   classDefinition
    |   functionDefinition
    ;

unitItem
    :   defenition
    |   statement
    ;

unit
    :   unitItem* EOF
    ;

ExtraSymbolCharacters: ( '#' | '@' | '$' | '`' | '?' )
    ;

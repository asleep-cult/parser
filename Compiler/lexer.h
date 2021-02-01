#include "vector.h"

#include <stdio.h>

typedef struct Token {
        int type;
        Vector value;
} Token;

typedef struct Lexer {
        int position;
        int lineno;
        int eof;
        char tail;
        FILE *fp;
        Vector tokens;
} Lexer;

Lexer Lexer_ParseFile(char *file_path);

enum TokenType {
	PLUS,
	MINUS,
	STAR,
	FSLASH,
	PERCENT,
	EQUAL,
	CARET,
	EXCLAMATION,
	QUESTION_MARK,
	TILDE,
	GREATER_THAN,
	LESS_THAN,
	VLINE,
	AMPERSAND,
	DOT,
	COMMA,
	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,
	LBRACKET,
	RBRACKET,
	AT,
	SEMICOLON,
	COLON,
	INTEGER,
	STRING,
	NAME,
	INVALID
};

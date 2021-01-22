#include <stdio.h>

typedef struct Token {
        int type;
        int value_size;
        char *value;
} Token;

typedef struct Lexer {
        int position;
        int lineno;
        int eof;
        int token_size;
        Token *current_token;
        FILE *fp;
        Token *tokens;
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
	RBRACKER,
	AT,
	SEMICOLON,
	COLON,
	INTEGER,
	STRING,
	NAME,
	INVALID
};

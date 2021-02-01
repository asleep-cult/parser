#include "lexer.h"
#include "vector.h"

#include <stdlib.h>

#define CHECK_DIGIT(value) (47 < c && 58 > c)

int get_token(char c)
{
	switch (c) {
	case '+': return PLUS;
	case '-': return MINUS;
	case '*': return STAR;
	case '/': return FSLASH;
	case '%': return PERCENT;
	case '=': return EQUAL;
	case '^': return CARET;
	case '!': return EXCLAMATION;
	case '?': return QUESTION_MARK;
	case '~': return TILDE;
	case '>': return GREATER_THAN;
	case '<': return LESS_THAN;
	case '|': return VLINE;
	case '&': return AMPERSAND;
	case '.': return DOT;
	case ',': return COMMA;
	case '(': return LPAREN;
	case ')': return RPAREN;
	case '{': return LBRACE;
	case '}': return RBRACE;
	case '[': return LBRACKET;
	case ']': return RBRACKET;
	case '@': return AT;
	case ';': return SEMICOLON;
	case ':': return COLON;
	default: return INVALID;
	}
}

char lexer_getc(Lexer *lexer)
{
        char c;
	if (lexer->tail != '\0') {
		c = lexer->tail;
		lexer->tail = '\0';
	}
	else {
		for (lexer->position++; ; lexer->position++) {
	                c = fgetc(lexer->fp);
	                if (c == EOF) {
	                        lexer->eof = 1;
	                        return EOF;
	                }
	                else if (c == '\n') {
	                        lexer->lineno++;
	                }
	                else if (c != ' ') {
	                        break;
	                }
	        }
	}

        Vector_Push(&lexer->current_token->value, c);
        return c;
}

void lexer_push_back(Lexer *lexer)
{
	Token *current_token = Vector_Get(&lexer->tokens, -1);
	Vector_Pop(current_token->value, -1);
	lexer->eof = 0;
	lexer->position--;
}

void lexer_parse_once(Lexer *lexer)
{
        Token *token = malloc(sizeof(Token));
        char c = lexer_getc(lexer);
        int token_type = get_token(c);

        if (token_type != INVALID) {
                new_token->type = token_type;
        }
        else if (CHECK_DIGIT(c)) {
                new_token->type = INTEGER;
		do {
			c = lexer_getc(lexer);
		} while(CHECK_DIGIT(c));

		lexer_push_back(lexer);
        }
}

Lexer Lexer_ParseFile(char *file_path)
{
        FILE *fp = fopen(file_path, "r");
        Lexer lexer = {
                .position = -1,
                .lineno = -1,
                .eof = 0,
		.tail = '\0',
                .fp = fp,
                .tokens = NULL
        };
	for (; !lexer->eof;) {
		lexer_parse_once(&lexer);
	}
}

#include "lexer.h"

#include <stdlib.h>

#define CHECK_DIGIT(value) (47 < c && 58 > c)

int get_token(char c)
{
	switch (c) {
	case '+':
		return PLUS;
	case '-':
		return MINUS;
	case '*':
		return STAR;
	case '/':
		return FSLASH;
	case '%':
		return PERCENT;
	case '=':
		return EQUAL;
	case '^':
		return CARET;
	case '!':
		return EXCLAMATION;
	case '?':
		return QUESTION_MARK;
	case '~':
		return TILDE;
	case '>':
		return GREATER_THAN;
	case '<':
		return LESS_THAN;
	case '|':
		return VLINE;
	case '&':
		return AMPERSAND;
	case '.':
		return DOT;
	case ',':
		return COMMA;
	case '(':
		return LPAREN;
	case ')':
		return RPAREN;
	case '{':
		return LBRACE;
	case '}':
		return RBRACE;
	case '[':
		return LBRACKET;
	case ']':
		return RBRACKER;
	case '@':
		return AT;
	case ';':
		return SEMICOLON;
	case ':':
		return COLON;
	default:
		return INVALID;
	}
}

Lexer Lexer_ParseFile(char *file_path)
{
        FILE *fp = fopen(file_path, "r");
        Lexer lexer = {
                .position = -1,
                .lineno = -1,
                .eof = 0,
                .token_size = -1,
                .fp = fp,
                .tokens = malloc(sizeof(Token))
        };
};

char lexer_getc(Lexer *lexer)
{
        char c;
        for (lexer->position++;; lexer->position++) {
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
        int value_size = lexer->current_token->value_size++;
        char *new_value = realloc(lexer->current_token->value, value_size);
        new_value[value_size] = c;
        lexer->current_token->value = new_value;
        return c;
};

void lexer_parse_once(Lexer *lexer)
{
        int token_size = lexer->token_size++;
        lexer->tokens[token_size] = (Token){
                .type = INVALID,
                .value_size = 0,
                .value = NULL
        }
        Token *new_token = lexer->tokens[token_size];
        char c = lexer_getc(lexer);
        int token_type = get_token(c);
        if (token_type != INVALID) {
                new_token->type = token_type;
        }
        else if (CHECK_DIGIT(c)) {
                new_token->type = INTEGER;
        }
        /* realloc tokens */
}

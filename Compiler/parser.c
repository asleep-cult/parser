#include "parser.h"
#include "lexer.h"

#include <stdlib.h>

Token *parser_neextt(Parser *parser)
{
        Token *token = &parser->tokens[parser->position];
        parser->position++;
        return token;
}

Node *parse_factor(Parser *parser)
{
        Node *node = malloc(sizeof(Node));
        while (1) {
                Token *tok = parser_nextt(parser);
                if (
                        tok->type == PLUS ||
                        tok->type == MINUS
                ) {
                        Node *new_node = malloc(sizeof(Node));
                        *node = (Node){
                                .type = UNARYOP,
                                .unary_operator = tok->type,
                                .unary_operand = new_node
                        };
                        node = new_node;
                }
                else if (tok->type == INTEGER) {
			Node *number = malloc(sizeof(Node));
			*number = (Node){
				.type = NUMBER,
				.number = tok->value
			};
			*node = (Node){
				.type = UNARYOP,
				.unary_operator = PLUS,
				.unary_operand = number
			};
			return node;
		}
        }
        return NULL;
}

Node *parse_term(Parser *parser)
{
        Node *left = parse_factor(parser);
        if (left == NULL) {
                return NULL;
        }

        while (1) {
                Token *tok = parser_nextt(parser);
                if (
                        tok->type == STAR ||
                        tok->type == FSLASH
                ) {
                        Node *right = parse_factor(parser);
                        if (right == NULL) {
                                return NULL;
                        }
                        Node *new_left = malloc(sizeof(Node));
                        *new_left = (Node){
                                .type = BINOP,
                                .binop_left = left,
                                .binop_operator = tok->type,
                                .binop_right = right
                        };
                        left = new_left;
                }
                else {
                        parser->position--;
                        break;
                }
        }
        return left;
}

Node *parse_expr(Parser *parser)
{
        Node *left = parse_term(parser);
        if (left == NULL) {
                return NULL;
        }

        while (1) {
                Token *tok = parser_nextt(parser);
                if (
                        tok->type == PLUS ||
                        tok->type == MINUS
                ) {
                        Node *right = parse_term(parser);
                        if (right == NULL) {
                                return NULL;
                        }
                        Node *new_left = malloc(sizeof(Node));
                        *new_left = (Node){
                                .type = BINOP,
                                .binop_left = left,
                                .binop_operator = tok->type,
                                .binop_right = right
                        };
                        left = new_left;
                }
                else {
                        break;
                }
        }
        return left;
}

Node *Parser_ParseTokens(Token *tokens)
{
        Parser parser = {
                .tokens = tokens,
                .position = 0
        };
        Node *node = parse_expr(&parser);
        return node;
}

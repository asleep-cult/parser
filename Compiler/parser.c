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
			Node* number = malloc(sizeof(Node));
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

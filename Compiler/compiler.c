#include "compile.h"
#include "parser.h"
#include "lexer.h"

void visit_node(Node *node)
{
        switch (node->type) {
        case NUMBER:
                // add the literal to Compiler->literals
        case BINOP:
                visit_node(node->binop_left);
                visit_node(node->binop_right);
                int opcode;
                switch (node->binop_operator) {
                case PLUS:
                        opcode = BINOP_ADD;
                case MINUS:
                        opcode = BINOP_MINUS;
                case STAR:
                        opcode = BINOP_MULTUPLY;
                case FSLASH:
                        opcode = BINOP_DIVIDE;
                }
                write_to_buffer(opcode);
        }
}

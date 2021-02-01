#include "compiler.h"
#include "parser.h"
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>

void emit(Code *code, int arg)
{
        Array_PushBack(code->buffer, arg);
}

void emit_literal(Code *code, int opcode, char *literal)
{
        emit(compiler, opcode);
        Vector_Push(code->literals, literal);
        emit(code->literals->length - 1);
}

void visit_node(Code *code, Node *node)
{
        switch (node->type) {
        case NUMBER:
                emit_literal(code, GET_NUMBER, node->number);
        case UNARYOP:
                int opcode;
                switch(node->unary_operator)
                {
                case PLUS:
                        opcode = UNARY_POSITIVE;
                case MINUS:
                        opcode = UNARY_NEGATIVE;
                }
                emit(code, opcode);
                visit_node(code, node->unary_operand);
        case BINOP:
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
                emit(code, opcode);
                visit_node(code, node->binop_left);
                visit_node(code, node->binop_right);
        }
}

Code Compile_AST(Node *node)
{
        Code code = {
                .types = Map_New(),
                .locals = Map_New(),
                .literals = Vector_New(),
                .buffer = Vector_New()
        };
        visit_node(&code, node);
        return code;
}

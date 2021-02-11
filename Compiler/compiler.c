#include "compiler.h"
#include "parser.h"
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>

void visit_node(Code *code, Node *node);

void emit(Code *code, char arg)
{
        Array_PushBack(code->buffer, arg);
}

void emit_literal(Code *code, char arg, char *literal)
{
        emit(compiler, arg);
        Vector_Push(code->literals, literal);
        emit(code->literals->length - 1);
}

void visit_number(Code *code, Node *node)
{
        emit_literal(code, GET_NUMBER, node->number);
}

void visit_unary_op(Code *code, Node *node)
{
        visit_node(code, node->unary_operand);
        int opcode;
        switch(node->unary_operator)
        {
        case PLUS:
                opcode = UNARY_POSITIVE;
        case MINUS:
                opcode = UNARY_NEGATIVE;
        }
        emit(code, opcode);
}

void visit_bin_op(Code *code, Node *node)
{
        visit_node(code, node->binop_right);
        visit_node(code, node->binop_left);
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
}

void visit_node(Code *code, Node *node)
{
        switch (node->type) {
        case NUMBER:
                visit_number(code, node);
        case UNARYOP:
                visit_unary_op(code, node);
        case BINOP:
                visit_bin_op(code, node);
        }
}

Code Compile_AST(Node *node)
{
        Code code = {
                .types = Map_New(),
                .locals = Map_New(),
                .literals = Vector_New(),
                .buffer = Array_New()
        };
        visit_node(&code, node);
        return code;
}

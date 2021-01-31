#include "compile.h"
#include "parser.h"
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>

void emit(Code *code, int arg)
{
        code->buffer_size++;
        int *new_buffer = realloc(
                code->buffer,
                sizeof(int) * code->buffer_size
        );
        code->buffer = new_buffer;
        code->buffer[code->buffer_size - 1] = arg;
}

void emit_literal(Code *code, int opcode, char *literal)
{
        emit(compiler, opcode);
        code->literals_size++;
        char *literals = realloc(
                code->literals,
                sizeof(char *) * code->literals_size
        );
        code->literals = literals;
        code->literals[code->literals_size - 1] = literal;
        emit(code->literals_size);
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

Compiler Compile_Node(Node *node)
{
        Block module;
        visit_node(&module, node);
        return compiler;
}

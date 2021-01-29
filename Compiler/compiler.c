#include "compile.h"
#include "parser.h"
#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>

void emit(Compiler *compiler, int arg)
{
        compiler->buffer_size++;
        int *new_buffer = realloc(
                compiler->buffer,
                sizeof(int) * compiler->buffer_size
        );
        compiler->buffer = new_buffer;
        compiler->buffer[compiler->buffer_size - 1] = arg;
}

void emit_literal(Compiler *compiler, int opcode, char *literal)
{
        emit(compiler, opcode);
        compiler->literals_size++;
        char *literals = realloc(
                compiler->literals,
                sizeof(char *) * compiler->literals_size
        );
        compiler->literals = literals;
        compiler->literals[compiler->literals_size - 1] = literal;
        emit(compiler->literals_size);
}

void visit_node(Compiler *compiler, Node *node)
{
        switch (node->type) {
        case NUMBER:
                emit_literal(compiler, GET_NUMBER, node->number);
        case UNARYOP:
                int opcode;
                switch(node->unary_operator)
                {
                case PLUS:
                        opcode = UNARY_POSITIVE;
                case MINUS:
                        opcode = UNARY_NEGATIVE;
                }
                emit(compiler, opcode);
                visit_node(compiler, node->unary_operand);
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
                emit(compiler, opcode);
                visit_node(node->binop_left);
                visit_node(node->binop_right);
        }
}

Compiler Compile_Node(Node *node)
{
        Compiler compiler = {
                .buffer = NULL,
                .buffer_size = 0,
                .literals = NULL,
                .literals_size = 0
        };
        visit_node(&compiler, node);
        return compiler;
}

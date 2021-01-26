#include "compile.h"
#include "parser.h"
#include "lexer.h"
#include "memory.h"
#include "integer.h"

#include <stdlib.h>

/* TODO: Don't use extern */
extern RuntimeState runtime_state;

void emit(Compiler *compiler, int opcode)
{
        compiler->buffer_size++;
        int *new_buffer = realloc(
                compiler->buffer,
                sizeof(int) * compiler->buffer_size
        );
        compiler->buffer = new_buffer;
        compiler->buffer[compiler->buffer_size] = opcode;
}

void visit_node(Compiler *compiler, Node *node)
{
        switch (node->type) {
        case NUMBER:
                Integer *integer = Integer_FromString(node->number);
                int location = runtime_state->heap->segment_size;
                //emit(compiler, LOAD_FROM_HEAP);
                //emit(compiler, location);
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
                //emit(compiler, opcode);
        }
}

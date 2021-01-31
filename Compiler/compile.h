#include "map.h"

enum Opcode {
        BINARY_ADD,
        BINARY_SUBTRACT,
        BINARY_DIVIDE,
        BINARY_MULTIPLY,
        BINARY_POWER,
        BINARY_AND,
        BINARY_OR,
        BINARY_XOR,
        UNARY_POSITIVE,
        UNARY_NEGATIVE,
        GET_NUMBER,
        GET_STRING
};

typedef struct Block Block;

typedef struct Code {
        Map types; /* Map<char *, Type *>: The types defined */
        Map locals; /* Map<char *, Type *>: The local names and their types */
        int *code; /* The bytecode */
        char *literals; /* The strings and integers used in the code */
        int literals_size;
        Block **inner_blocks;
        int *buffer;
        int buffer_size;
} Code;

typedef struct block_arg {
        char *name;
        char *default
} block_arg;

typedef struct Block {
        char *name;
        int keyword;
        block_arg *largs;
        int largs_len
        block_arg *rargs;
        int rargs_length;
        Code *code;
};

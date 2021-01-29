#include "integer.h"
#include "string.h"

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

typedef struct Compiler {
        int *buffer;
        int buffer_size;
        char *literals;
        int literals_size;
};

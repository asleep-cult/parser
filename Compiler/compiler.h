#include "map.h"
#include "vector.h"
#include "array.h"

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

typedef struct Code {
        Map *types; /* Map<char *, Type *>: The types defined */
        Map *locals; /* Map<char *, Type *>: The local names and their types */
        Vector *literals; /* Vector<char *> The strings and integers used in the code */
        Array *buffer;
        struct Code *inner_code;
} Code;

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
        GET_LITERAL
}

typedef struct Compiler {
        int *buffer;
        int buffer_size;
        // void *literals;
        int literal_size;
};

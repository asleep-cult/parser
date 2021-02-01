#include "parser.h"
#include "lexer.h"
#include "compiler.h"

typedef struct void *(*call_stack_function)();

typedef struct Runtime {
        call_stack_function *call_stack;
        int call_stack_size;
} Runtime;

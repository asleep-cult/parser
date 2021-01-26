#include "object.h"

typedef Object *(*Function_OneArg)(Object *);
typedef Object *(*Function_TwoArgs)(Object *, Object *)

typedef struct Type {
        char *name;
        Function_OneArg descr;
        Function_TwoArgs add;
        Function_TwoArgs subtract;
        Function_TwoArgs multiply;
        Function_TwoArgs divide;
        Function_OneArg unary_positive;
        Function_OneArg unary_positive;
} Type;

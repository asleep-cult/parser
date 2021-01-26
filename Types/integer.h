#include "object.h"

typedef struct Integer {
        Object;
        long *buffer;
        int buffer_length;
} Integer;

Integer *Integer_FromString(char *string, int string_size);
Integer *Integer_FromLong(long value);
char *Integer_ToString(Integer *integer);
Integer *Integer_Add(Integer *operand);
Integer *Integer_Subtract(Integer *operand);
Integer *Integer_Multiply(Integer *operand);
Integer *Integer_Divide(Integer *operand);

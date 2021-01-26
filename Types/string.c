#include "string.h"
#include "memory.h"
#include "type.h"

#include <string.h>

extern RuntimeState runtime_state;

Type string_type = {
        .decr = &string_descr,
        .add = NULL,
        .subtract = NULL,
        .multiply = NULL,
        .divide = NULL,
        .unary_positive = NULL,
        .unary_negative = NULL
};

Object *String_FromString(char *string)
{
        String *string = RuntimeHeap_Malloc(
                runtime_state->heap,
                sizeof(String)
        );
        string->type = &string_type;
        int length = strlen(string);
        string->length = length;
        string->buffer = string;
        return (Object *)string;
}

Object *String_FromStringAndLength(char *string, int length)
{
        String *string = RuntimeHeap_Malloc(
                runtime_state->heap,
                sizeof(String)
        );
        string->type = &string_type;
        string->length = length;
        string->buffer = string;
        return (Object *)string;
}

char *String_ToString(Object *string)
{
        return ((String *)string)->buffer;
}

Object *string_descr(Object *string) {
        return string;
}

#include "integer.h"
#include "memory.h"

#define CHAR_DIGIT_OFFSET 48

/* TODO: Don't use extern */
extern RuntimeState runtime_state;

Object *Integer_FromLong(long value)
{
        Integer *integer = RuntimeHeap_Malloc(
                runtime_state->heap,
                sizeof(Integer)
        );
        Integer *integer = segment->data;
        integer->buffer_length = 0;
        integer->buffer = malloc(sizeof(long));
        integer->buffer[0] = value;
        return (Object *)integer;
}

Object *Integer_FromString(char *string, int string_size)
{
        /* TODO: Check for overflow and realloc */
        Integer *integer = Integer_FromLong(0);
        long *curr_long = &integer->buffer[0];
        for (int i = 0; i < string_size; i++) {
                int digit = string[i] - CHAR_DIGIT_OFFSET;
                *curr_long += digit;
                *curr_long *= 10;
        }
        return (Object *)integer;
}

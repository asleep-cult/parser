#include "object.h"

typedef struct String {
        Object;
        char *buffer;
        int length;
} String;

Object *String_FromString(char *string);
Object *String_FromStringAndLength(char *string, int length);
char *String_ToString(Object *string);

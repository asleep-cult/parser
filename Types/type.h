#include "map.h"

enum TypeType {
        LITERAL,
        STRUCT,
        GENERIC
};

typedef struct Type {
        int type;
        char *name;
        size_t size;
        Map properties;
} Type;

size_t Type_GetSize(Type *type);
size_t Type_GetPropertyOffset(Type *type, char *name);
Type *Type_FromGeneric(Type *generic_type, Type *type_arg);

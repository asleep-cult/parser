#include "map.h"

typedef struct Type Type;

typedef struct LiteralType {
        size_t size;
} LiteralType;

typedef struct StructType {
        Map properties;
} StructType;

typedef struct Type {
        int literal;
        char *name;
        union {
                LiteralType;
                StructType;
        }
} Type;

size_t Type_GetSize(Type *type);
size_t Type_GetPropertyOffset(Type *type, char *name);

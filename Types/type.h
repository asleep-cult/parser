typedef struct Type Type;

typedef struct LiteralType {
        char *name;
        size_t size;
} LiteralType;

typedef struct StructType {
        char *name;
        char **property_names;
        Type **properties;
        int properties_size;
} StructType;

typedef struct Type {
        int literal;
        union {
                LiteralType;
                StructType;
        }
} Type;

size_t Type_GetSize(Type *type);
int Type_GetPropertyOffset(Type *type, char *name);

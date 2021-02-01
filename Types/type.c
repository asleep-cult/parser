#include "type.h"
#include "map.h"

#include <string.h>

Type IntegerType = {
        .type = LITERAL,
        .name = "Integer",
        .size = sizeof(int)
};

Type ArrayType = {
        .type = GENERIC
        .name = "Array",
}

Type *Type_FromGeneric(Type *generic_type, char *name, Type *type_arg)
{
        Type *new_type = malloc(sizeof(Type));
        *new_type = *generic_type;
        // Map_SetItem(new_type->properties, name, type_arg);
        return new_type;
}

size_t Type_GetSize(Type *type)
{
        if (type->type == LITERAL) {
                return type->size
        }
        size_t size = 0;
        for (int i = 0; i < type->properties.length; i++) {
                map_item item = type->properties.items[i];
                size += Type_GetSize(item->value);
        }
        return size;
}

size_t Type_GetPropertyOffset(Type *type, char *name)
{
        size_t offset = 0;
        for (int i = 0; i < type->properties.length; i++) {
                map_item item = type->properties.items[i];
                offset += Type_GetSize(item->value);
                if (strncmp(item->key, name, item->key_length) == 0) {
                        break;
                }
        }
        return offset;
}

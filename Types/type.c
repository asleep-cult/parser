#include "type.h"

#include <string.h>

size_t Type_GetSize(Type *type)
{
        if (type->literal) {
                return type->size
        }
        size_t size = 0;
        for (int i = 0; i < type->properties.length; i++) {
                size += Type_GetSize(Map_GetItem(type->properties, i));
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

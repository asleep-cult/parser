#include "type.h"

#include <string.h>

size_t Type_GetSize(Type *type)
{
        if (type->literal) {
                return type->size
        }
        size_t size = 0;
        for (int i = 0; i < type->properties_size; i++) {
                size += Type_GetSize(type->properties[i]);
        }
        return size;
}

int Type_GetPropertyOffset(Type *type, char *name)
{
        int offset = 0;
        for (int i = 0; i < type->properties_size; i++) {
                offset += Type_GetSize(type->properties[i]);
                if (strcmp(type->property_names[i], name) == 0) {
                        break;
                }
        }
        return offset;
}

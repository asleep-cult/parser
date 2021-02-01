#include "vector.h"

#include <stdlib.h>
#include <string.h>

int Vector_Push(Vector *vector, void *item)
{
        int size = vector->size++;
        void **new_items = realloc(
                                vector->items,
                                sizeof(void *) * size);

        if (new_items == NULL) {
                return 0;
        }

        vector->items = new_items;
        vector->items[size - 1] = item;
        return 1;
}

void *Vector_Get(Vector *vector, int index)
{
        if (index < 0) {
                index = vector->length - index;
        }
        if (index >= vector->length) {
                return NULL;
        }

        return vector->items[index];
}

void *Vector_Pop(Vector *vector, int index)
{
        if (index < 0) {
                index = vector->length - index;
        }
        if (index >= vector->length) {
                return NULL;
        }

        void *item = Vector_Get(vector, index);
        int size = vector->size--;

        memmove(
                vector->items + index,
                vector->items + index + 1,
                sizeof(void *) * (size - index));

        void **new_items = realloc(
                                vector->items,
                                sizeof(void *) * (size));

        if (new_items == NULL) {
                return NULL;
        }

        vector->items = new_items;
        return item;
}

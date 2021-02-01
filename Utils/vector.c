#include "vector.h"

#include <stdlib.h>
#include <string.h>

Vector *Vector_New()
{
        Vector *vector = malloc(sizeof(Vector));
        vector->items = NULL;
        vector->length = 0;
        return vector;
}

int Vector_Push(Vector *vector, void *item)
{
        int length = vector->length++;
        void **new_items = realloc(
                                vector->items,
                                sizeof(void *) * length);

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
                index = vector->length + index;
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
        int length = vector->length--;

        memmove(
                vector->items + index,
                vector->items + index + 1,
                sizeof(void *) * (length - index));

        void **new_items = realloc(
                                vector->items,
                                sizeof(void *) * (length));

        if (new_items == NULL) {
                return NULL;
        }

        vector->items = new_items;
        return item;
}

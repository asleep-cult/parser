#include "array.h"

#include <stdlib.h>

Array *Array_New()
{
        Array *array = malloc(sizeof(Array));
        array->items = NULL;
        array->length = 0;
        return array;
}

int Array_PushBack(Array *array, int value)
{
        int length = array->length++;
        char *new_items = realloc(
                                array->items,
                                sizeof(int) * length);

        if (new_items == NULL) {
                return 0;
        }
        array->items = new_items;
        array->items[length - 1] = value;
        return 1;
}

int Array_PopBack(Array *array)
{
        int length = array->length--;
        char *new_items = realloc(
                                array->items,
                                sizeof(char) * length);

        if (new_items == NULL) {
                return 0;
        }
        array->items = new_items;
        return 1;
}

int Array_Get(Array *array, int index)
{
        if (index < 0) {
                index = array->length + index;
        }
        if (index >= array->length) {
                return 0;
        }

        return array->items[index];
}

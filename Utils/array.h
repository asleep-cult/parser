typedef struct Array {
        int *items;
        int length;
} Array;

Array *Array_New();
int Array_PushBack(Array *array, int value);
int Array_PopBack(Array *array);
int Array_Get(Array *array, int index);

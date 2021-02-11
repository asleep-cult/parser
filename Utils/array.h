typedef struct Array {
        char *items;
        int length;
} Array;

Array *Array_New();
int Array_PushBack(Array *array, char value);
int Array_PopBack(Array *array);
char Array_Get(Array *array, int index);

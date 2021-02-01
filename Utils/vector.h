typedef struct Vector {
        void **items;
        int length;
} Vector;

Vector *Vector_New();
int Vector_Push(Vector *vector, void *item);
void *Vector_Get(Vector *vector, int index);
void *Vector_Pop(Vector *vector, int index);

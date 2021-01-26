#include "type.h"

typedef struct Object {
        Type *type;
}

Object *Object_Descr(Object *object);
Object *Object_Add(Object *object, Object *operand);
Object *Object_Subtract(Object *object, Object *operand);
Object *Object_Multiply(Object *object, Object *operand);
Object *Object_Divide(Object *object, Object *operand);
Object *Object_UnaryPositive(Object *object);
Object *Object_UnaryNegative(Object *object);

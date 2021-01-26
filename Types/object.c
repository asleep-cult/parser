#include "object.h"
#include "type.h"
#include "string.h"

#include <stdio.h>

Object *Object_Descr(Object *object)
{
        Type *type = object->type;
        Function_OneArg func = type->descr;
        if (func == NULL) {
                char *fmt = sprintf("{Object <type: '%s'>}", type->name);
                return String_FromString(fmt);
        }
        return func(object);
}

Object *Object_Add(Object *object, Object *operand)
{
        Type *type = object->type;
        Function_TwoArgs func = type->add;
        if (func == NULL) {
                return NULL;
        }
        return func(object, operand);
}

Object *Object_Subtract(Object *object, Object *operand)
{
        Type *type = object->type;
        Function_TwoArgs func = type->subtract;
        if (func == NULL) {
                return NULL;
        }
        return func(object, operand);
}

Object *Object_Multiply(Object *object, Object *operand)
{
        Type *type = object->type;
        Function_TwoArgs func = type->multiply;
        if (func == NULL) {
                return NULL;
        }
        return func(object, operand);
}

Object *Object_Divide(Object *object, Object *operand)
{
        Type *type = object->type;
        Function_TwoArgs func = type->divide;
        if (func == NULL) {
                return NULL;
        }
        return func(object, operand);
}

Object *Object_UnaryPositive(Object *object)
{
        Type *type = object->type;
        Function_OneArg func = type->unary_positive;
        if (func == NULL) {
                return NULL;
        }
        return func(object);
}

Object *Object_UnaryNegative(Object *object)
{
        Type *type = object->type;
        Function_OneArg func = type->unary_negative;
        if (func == NULL) {
                return NULL;
        }
        return func(object);
}

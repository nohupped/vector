#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#define VEC_LENGTH 9



#define vector_declare(TYPE) \
    struct { \
    size_t* vector_length; \
    size_t* current_index; \
    TYPE* vector; \
}

#define vector_initialize(VECTOR) do { \
    if (!(VEC_LENGTH)) { \
        printf("Cannot have vector length defined as 0\n"); \
        abort(); \
    } \
    VECTOR.vector = calloc(sizeof(*(VECTOR).vector), (VEC_LENGTH));\
    if (!(VECTOR).vector) { \
        printf("Calloc failed"); \
        abort(); \
    } \
    ((VECTOR).vector_length) = (size_t *) calloc(sizeof(size_t), (1)); \
    (*(VECTOR).vector_length) =  VEC_LENGTH; \
    ((VECTOR).current_index) = (size_t *) calloc(sizeof(size_t), (1)); \
    (*(VECTOR).current_index) = 0; \
} while(0)

#endif

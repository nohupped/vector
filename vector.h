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
    ((VECTOR).vector_length) = (size_t *) calloc(sizeof(size_t), (1)); \
    (*(VECTOR).vector_length) =  VEC_LENGTH; \
    (VECTOR).vector = calloc(sizeof(*(VECTOR).vector), (*(VECTOR).vector_length));\
    if (!(VECTOR).vector) { \
        printf("Calloc failed"); \
        abort(); \
    } \
    ((VECTOR).current_index) = (size_t *) calloc(sizeof(size_t), (1)); \
    (*(VECTOR).current_index) = 0; \
} while(0)


#define vector_push(VECTOR, DATA) do { \
    if (((*(VECTOR).current_index) + (1)) <= (*(VECTOR).vector_length)) { \
        (VECTOR).vector[((*(VECTOR).current_index))] = DATA; \
        (*(VECTOR).current_index) += 1; \
        } \
    else { \
        printf("Reallocating memory at size %lu\n", (*(VECTOR).vector_length)); \
        (*(VECTOR).vector_length) = ((*(VECTOR).vector_length) + VEC_LENGTH); \
        (VECTOR).vector = realloc((VECTOR).vector, (*(VECTOR).vector_length) * sizeof(*(VECTOR).vector)); \
        if (!(VECTOR).vector) { \
            printf("Realloc failed at size %lu", (*(VECTOR).vector_length)) ;\
            abort(); \
        } \
        if (!(VECTOR).vector) { \
            printf("Calloc failed"); \
            abort(); \
        } \
        (VECTOR).vector[((*(VECTOR).current_index))] = DATA; \
        (*(VECTOR).current_index) += 1; \
    } \
} while(0)

#endif

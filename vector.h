#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>

#define VEC_LENGTH 64

#ifdef DEBUG
#define DEBUG_PRINT(...) do{ fprintf(stdout, __VA_ARGS__); } while(0)
#else
#define DEBUG_PRINT(...) do{ } while (0)
#endif


#define vector_declare(TYPE) \
    struct { \
    size_t* vector_length; \
    size_t* current_index_plus_one; \
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
    ((VECTOR).current_index_plus_one) = (size_t *) calloc(sizeof(size_t), (1)); \
    (*(VECTOR).current_index_plus_one) = 0; \
} while(0)


#define vector_push_back(VECTOR, DATA) do { \
    if (((*(VECTOR).current_index_plus_one) + (1)) <= (*(VECTOR).vector_length)) { \
        (VECTOR).vector[((*(VECTOR).current_index_plus_one))] = DATA; \
        (*(VECTOR).current_index_plus_one) += 1; \
        } \
    else { \
        DEBUG_PRINT("Reallocating memory at size %lu\n", (*(VECTOR).vector_length)); \
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
        (VECTOR).vector[((*(VECTOR).current_index_plus_one))] = DATA; \
        (*(VECTOR).current_index_plus_one) += 1; \
    } \
} while(0)

#define vector_pop_back(VECTOR) do { \
    if (*(VECTOR).vector_length <= 0) { \
        printf("Last element already popped, no more elements to pop\n"); \
        break; \
    } \
    else { \
        *(VECTOR).vector_length -= 1; \
        (VECTOR).vector = realloc((VECTOR).vector, (*(VECTOR).vector_length) * sizeof(*(VECTOR).vector)); \
        DEBUG_PRINT("vector resized to %lu\n", *(VECTOR).vector_length - (1));} \
     \
} while(0)

#endif

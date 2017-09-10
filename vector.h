#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define VEC_LENGTH 64

#ifdef DEBUG
#define DEBUG_PRINT(...) do{ fprintf(stdout, __VA_ARGS__); } while(0)
#else
#define DEBUG_PRINT(...) do{ } while (0)
#endif

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


// size_t* vector_capacity = number of elements the vector can hold. Starts with 0.
// size_t* current_index = the index to which the next push back will be appended.
#define vector_declare(TYPE) \
    struct { \
    size_t* vector_capacity; \
    size_t* current_index; \
    TYPE* vector; \
}


#define vector_initialize(VECTOR) do { \
    if (!(VEC_LENGTH)) { \
        printf("vector_initialize: Cannot have vector length defined as 0\n"); \
        abort(); \
    } \
    DEBUG_PRINT("vector_initialize: Default vector capacity defined is %d\n", VEC_LENGTH); \
    ((VECTOR).vector_capacity) = (size_t *) calloc(sizeof(size_t), (1)); \
    pthread_mutex_lock(&mutex); \
    (*(VECTOR).vector_capacity) =  VEC_LENGTH; \
    pthread_mutex_unlock(&mutex); \
    DEBUG_PRINT("vector_initialize: callocing vector memory to  %lu\n", sizeof(*(VECTOR).vector) * (*(VECTOR).vector_capacity)); \
    (VECTOR).vector = malloc(sizeof(*(VECTOR).vector) * (*(VECTOR).vector_capacity));\
    (VECTOR).current_index = NULL; \
    if (!(VECTOR).vector) { \
        printf("vector_initialize: Calloc failed"); \
        abort(); \
    } \
} while(0)


#define vector_push_back(VECTOR, DATA) do { \
    if ((VECTOR).current_index == NULL) { \
        DEBUG_PRINT("vector_push_back: Current index is null, initializing to 0\n"); \
        ((VECTOR).current_index) = (size_t *) calloc(sizeof(size_t), (1)); \
        (*(VECTOR).current_index) = 0; \
        pthread_mutex_lock(&mutex); \
        (VECTOR).vector[((*(VECTOR).current_index))] = DATA; \
        pthread_mutex_unlock(&mutex); \
    } else if (((*(VECTOR).current_index) + (1)) <= ((*(VECTOR).vector_capacity) - 1)) { \
        DEBUG_PRINT("vector_push_back: current_index %lu <= vector_capacity %lu\n", (*(VECTOR).current_index), (*(VECTOR).vector_capacity));\
        pthread_mutex_lock(&mutex); \
        (*(VECTOR).current_index) += 1; \
        (VECTOR).vector[((*(VECTOR).current_index))] = DATA; \
        pthread_mutex_unlock(&mutex); \
        } \
    else { \
        DEBUG_PRINT("vector_push_back: Reallocating memory at vector capacity from %lu to %lu\n", (*(VECTOR).vector_capacity), ((*(VECTOR).vector_capacity) + VEC_LENGTH)); \
        (*(VECTOR).vector_capacity) = ((*(VECTOR).vector_capacity) + VEC_LENGTH); \
        (VECTOR).vector = realloc((VECTOR).vector, (*(VECTOR).vector_capacity) * sizeof(*(VECTOR).vector)); \
        if (!(VECTOR).vector) { \
            printf("vector_push_back: Realloc failed at size %lu", (*(VECTOR).vector_capacity)) ;\
            abort(); \
        } \
        if (!(VECTOR).vector) { \
            printf("vector_push_back: Calloc failed"); \
            abort(); \
        } \
        (*(VECTOR).current_index) += 1; \
        (VECTOR).vector[((*(VECTOR).current_index))] = DATA; \
    } \
} while(0)


#define vector_pop_back(VECTOR) do { \
    if ((*(VECTOR).current_index == 0)){ \
        printf("vector_pop_back: Cannot pop the only index remaining. Doing nothing. Use vector_free(VECTOR) instead.\n"); \
    } else { \
        if ( ((*(VECTOR).vector_capacity) - ((*(VECTOR).current_index))) > VEC_LENGTH) { \
            DEBUG_PRINT("vector_pop_back: vector_capacity %lu - current_index %lu > VEC_LENGTH %d\n", *(VECTOR).vector_capacity, (*(VECTOR).current_index), VEC_LENGTH) ; \
            size_t reduced_capacity = (*(VECTOR).current_index) * sizeof(*(VECTOR).vector);  \
            (*(VECTOR).vector_capacity) =  reduced_capacity; \
            (VECTOR).vector = realloc((VECTOR).vector, reduced_capacity); \
            DEBUG_PRINT("vector_pop_back: vector shrunk to %lu\n", *(VECTOR).vector_capacity - (1)); \
        }\
        DEBUG_PRINT("vector_pop_back: Before decrementing index: Current vector_capacity is %lu and current_index is %lu\n", *(VECTOR).vector_capacity, *(VECTOR).current_index); \
        *(VECTOR).current_index  -= 1; \
        DEBUG_PRINT("vector_pop_back: After decrementing index: Current vector_capacity is %lu and current_index is %lu\n", *(VECTOR).vector_capacity, *(VECTOR).current_index); \
   }\
} while(0)


#define vector_free(VECTOR) do { \
    DEBUG_PRINT("vector_free: Freeing current_index pointer\n"); \
    free((VECTOR).current_index); \
    DEBUG_PRINT("vector_free: Freeing vector_capacity pointer\n"); \
    free((VECTOR).vector_capacity); \
    DEBUG_PRINT("vector_free: Freeing vector data pointer\n"); \
    free((VECTOR).vector); \
} while(0)
#define vector_get_current_index_data(VECTOR) ((VECTOR).current_index ==  NULL ? (NULL) : &((VECTOR).vector[((*(VECTOR).current_index))]))

#define vector_get_current_index_number(VECTOR) (*(VECTOR).current_index == 0 ? (NULL) : ((*(VECTOR).current_index)))
#endif

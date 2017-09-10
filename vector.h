#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define VEC_LENGTH 64

#ifdef DEBUG
#define DEBUG_PRINT(...) do{ fprintf(stderr, __VA_ARGS__); } while(0)
#else
#define DEBUG_PRINT(...) do{ } while (0)
#endif

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


// size_t* vector_capacity = number of elements the vector can hold. Starts with 0.
// size_t* current_index_plus_one = the index to which the next push back will be appended.
#define vector_declare(TYPE) \
    struct { \
    size_t* vector_capacity; \
    size_t* current_index_plus_one; \
    TYPE* vector; \
}

#define vector_initialize(VECTOR) do { \
    if (!(VEC_LENGTH)) { \
        printf("Cannot have vector length defined as 0\n"); \
        abort(); \
    } \
    ((VECTOR).vector_capacity) = (size_t *) calloc(sizeof(size_t), (1)); \
    pthread_mutex_lock(&mutex); \
    (*(VECTOR).vector_capacity) =  VEC_LENGTH; \
    pthread_mutex_unlock(&mutex); \
    (VECTOR).vector = calloc(sizeof(*(VECTOR).vector), (*(VECTOR).vector_capacity));\
    if (!(VECTOR).vector) { \
        printf("Calloc failed"); \
        abort(); \
    } \
    ((VECTOR).current_index_plus_one) = (size_t *) calloc(sizeof(size_t), (1)); \
    pthread_mutex_lock(&mutex); \
    (*(VECTOR).current_index_plus_one) = 0; \
    pthread_mutex_unlock(&mutex); \
} while(0)


#define vector_push_back(VECTOR, DATA) do { \
    if (((*(VECTOR).current_index_plus_one) + (1)) <= (*(VECTOR).vector_capacity)) { \
        pthread_mutex_lock(&mutex); \
        (VECTOR).vector[((*(VECTOR).current_index_plus_one))] = DATA; \
        (*(VECTOR).current_index_plus_one) += 1; \
        pthread_mutex_unlock(&mutex); \
        } \
    else { \
        DEBUG_PRINT("Current vector length is %lu\n", (*(VECTOR).vector_capacity)); \
        DEBUG_PRINT("Reallocating memory at vector capacity from %lu to %lu\n", (*(VECTOR).vector_capacity), ((*(VECTOR).vector_capacity) + VEC_LENGTH)); \
        (*(VECTOR).vector_capacity) = ((*(VECTOR).vector_capacity) + VEC_LENGTH); \
        (VECTOR).vector = realloc((VECTOR).vector, (*(VECTOR).vector_capacity) * sizeof(*(VECTOR).vector)); \
        if (!(VECTOR).vector) { \
            printf("Realloc failed at size %lu", (*(VECTOR).vector_capacity)) ;\
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
    if (*(VECTOR).vector_capacity <= 0) { \
        printf("Last element already popped, no more elements to pop\n"); \
        break; \
    } \
    else { \
        *(VECTOR).vector_capacity -= sizeof(*(VECTOR).vector); \
        *(VECTOR).current_index_plus_one  -= 1; \
        (VECTOR).vector = realloc((VECTOR).vector, (*(VECTOR).current_index_plus_one) * sizeof(*(VECTOR).vector)); \
        DEBUG_PRINT("vector re-sized to %lu\n", *(VECTOR).vector_capacity - (1));} \
        DEBUG_PRINT("Current vector_capacity is %lu and current_index_plus_one is %lu\n", *(VECTOR).vector_capacity, *(VECTOR).current_index_plus_one); \
} while(0)

#define vector_get_current_index_data(VECTOR) ( *(VECTOR).current_index_plus_one < 1 ? (NULL) : &((VECTOR).vector[((*(VECTOR).current_index_plus_one) - 1)]))

#define vector_get_current_index_number(VECTOR) (*(VECTOR).current_index_plus_one < 1 ? (NULL) : ((*(VECTOR).current_index_plus_one) - 1))
#endif

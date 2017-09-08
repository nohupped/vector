#include <stdio.h>
#include "vector.h"

int main() {

#define VEC_LENGTH 0
    vector_declare(int) v;
    vector_initialize(v);
    vector_declare(char) c;
    vector_initialize(c);
    printf("%lu", *v.vector_length);
    printf("%lu", *c.current_index);

}

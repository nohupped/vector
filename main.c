#include <stdio.h>
// Define DEBUG flag above #include <vector.h> to enable DEBUG flag and DEBUG output to STDOUT.
#define DEBUG
#include "vector.h"
#include <stdbool.h>

#undef VEC_LENGTH
#define VEC_LENGTH 2



struct person {
    int age;
    char* name;
};

struct animal {
    char* name;
    bool isdog;
};

int main() {
    // Declare and initialize a vector of type char
    vector_declare(char) c;
    vector_initialize(c);

    // declare a char pointer to assign a single char value from the char vector
    char* tmp;

    // get current index data of the initialized but empty vector. Returns NULL here.
    tmp = vector_get_current_index_data(c);
    if (tmp == NULL) {
        printf("Null value received\n");
    } else {
        printf("printing current index, which is %c\n", *tmp);
    }

    // push char 'h' at the end of the char vector.
    vector_push_back(c, 'h');
    // get current index of the non-empty vector.
    tmp = vector_get_current_index_data(c);
    if (tmp == NULL) {
        printf("Null value received\n");
    } else {
        printf("printing current index, which is %c\n", *tmp);
    }

    vector_push_back(c, 'e');
    vector_push_back(c, 'l');
    vector_push_back(c, 'l');
    vector_push_back(c, 'o');
    tmp = vector_get_current_index_data(c);
    printf("printing last index, which is %c\n", *tmp);

    printf("Full char array in vector is \"%s\"\n", c.vector);

    printf("popping %c\n", *vector_get_current_index_data(c));
    vector_pop_back(c);
    printf("popping %c\n", *vector_get_current_index_data(c));
    vector_pop_back(c);
    printf("popping %c\n", *vector_get_current_index_data(c));
    vector_pop_back(c);
    printf("popping %c\n", *vector_get_current_index_data(c));
    vector_push_back(c, '\0');
    printf("Full char array in vector is \"%s\"\n", c.vector);
    vector_pop_back(c);
    vector_push_back(c, '-');
    vector_push_back(c, 'm');
    vector_push_back(c, 'a');
    vector_push_back(c, 'n');
    printf("Full char array in vector is \"%s\"\n", c.vector);

    vector_free(c);


    vector_declare(struct person) z;
    vector_initialize(z);

    struct person person1;
    person1.name = "person 1";
    person1.age = 999;
    struct person* tmp1 = vector_get_current_index_data(z);
    if (tmp1 == NULL) {
        printf("Null value received\n");
    }
    vector_push_back(z, person1);
    struct person* current_index = vector_get_current_index_data(z);
    printf("%s\n", current_index->name);

    struct person person2;
    person2.name = "person 2";
    person2.age = 999;
    tmp1 = vector_get_current_index_data(z);
    if (tmp1 == NULL) {
        printf("Null value received\n");
    }
    vector_push_back(z, person2);
    current_index = vector_get_current_index_data(z);
    printf("%s\n", current_index->name);
    vector_free(z);

    struct animal dog;
    dog.name = "doggie";
    dog.isdog = true;
    vector_declare(struct animal) creature;
    vector_initialize(creature);
    vector_push_back(creature, dog);
    struct animal* animal_current_index = vector_get_current_index_data(creature);
    printf("%s\n", animal_current_index->name);



}

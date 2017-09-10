# vector

A lame attempt to emulate C++ `std::vector`. This will create a dynamically expanding and shrinking vector of any type - builtin or structs using macros.

#### flags and values:
 - `#define VEC_LENGTH 64` to define the vector capacity. Can over-ride in main file by 
 ```
 #undef VEC_LENGTH
#define VEC_LENGTH 2
```
 - `DEBUG` to enable debug printing from within the macro.
#### functions:
- macro `vector_declare` for generating an `anonymous struct` to create the vector of a type, like `vector_declare(char) c;` or `vector_declare(struct animal) creature;`
- macro `vector_initialize` to initialize the vector's struct members.
- macro `vector_push_back` to append to the vector. If a different data type of a different size is pushed, it can cause undefined behaviour.
- macro `vector_pop_back` for removing the last element from the end of the vector. This will decrement the current_index and will only do a re-alloc to shrink the memory block if the `vector_capacity - current_index > VEC_LENGTH`. Attempt to access values outside the bounds is undefined behaviour.
- macro `vector_free` will free all the pointers in the vector's struct. Attempt to access the same vector's data after free is undefined behaviour.
- macro `vector_get_current_index_data` will return the last appended value to the vector.
- macro `vector_get_current_index_number` will return the last appended value's index number.
#### Todo: add mutex for thread-safety.

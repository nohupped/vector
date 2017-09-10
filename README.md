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
#### Sample output from main.c here with `DEBUG` flag enabled:
```
./vector


vector_initialize: Default vector capacity defined is 2
vector_initialize: mallocing vector memory to  2
Null value received
vector_push_back: Current index is null, initializing to 0
printing current index, which is h
vector_push_back: current_index 0 <= vector_capacity 2
vector_push_back: Reallocating memory at vector capacity from 2 to 4
vector_push_back: current_index 2 <= vector_capacity 4
vector_push_back: Reallocating memory at vector capacity from 4 to 6
printing last index, which is o
Full char array in vector is "hello"
popping o
vector_pop_back: Before decrementing index: Current vector_capacity is 6 and current_index is 4
vector_pop_back: After decrementing index: Current vector_capacity is 6 and current_index is 3
popping l
vector_pop_back: vector_capacity 6 - current_index 3 > VEC_LENGTH 2
vector_pop_back: vector shrunk to 2
vector_pop_back: Before decrementing index: Current vector_capacity is 3 and current_index is 3
vector_pop_back: After decrementing index: Current vector_capacity is 3 and current_index is 2
popping l
vector_pop_back: Before decrementing index: Current vector_capacity is 3 and current_index is 2
vector_pop_back: After decrementing index: Current vector_capacity is 3 and current_index is 1
popping e
vector_push_back: current_index 1 <= vector_capacity 3
Full char array in vector is "he"
vector_pop_back: Before decrementing index: Current vector_capacity is 3 and current_index is 2
vector_pop_back: After decrementing index: Current vector_capacity is 3 and current_index is 1
vector_push_back: current_index 1 <= vector_capacity 3
vector_push_back: Reallocating memory at vector capacity from 3 to 5
vector_push_back: current_index 3 <= vector_capacity 5
vector_push_back: Reallocating memory at vector capacity from 5 to 7
Full char array in vector is "he-man"
vector_free: Freeing current_index pointer
vector_free: Freeing vector_capacity pointer
vector_free: Freeing vector data pointer
vector_initialize: Default vector capacity defined is 2
vector_initialize: mallocing vector memory to  32
Null value received
vector_push_back: Current index is null, initializing to 0
person 1
vector_push_back: current_index 0 <= vector_capacity 2
person 2
vector_free: Freeing current_index pointer
vector_free: Freeing vector_capacity pointer
vector_free: Freeing vector data pointer
vector_initialize: Default vector capacity defined is 2
vector_initialize: mallocing vector memory to  32
vector_push_back: Current index is null, initializing to 0
doggie
```

#### Not thread-safe now.

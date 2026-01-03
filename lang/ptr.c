#include <stdio.h>
#include <stdlib.h>

void ptr_basics() {
  // creating pointer
  int ten = 10;
  int *pointer_to_ten = &ten;
  // int *invalid_ptr = &10; // Error: cannot take the address of an rvalue
  // literal

  // dereferencing pointer
  *pointer_to_ten = 20;

  // pointer arithmetic - arrays are built on this principle
  printf("%p\n", (void *)pointer_to_ten);
  // adding 2 to ptr will move it by 2 * sizeof(int) bytes
  printf("%p\n", (void *)(pointer_to_ten + 2));
  // similarly adding 6 will move it by 6 * sizeof(int) bytes
  printf("%p\n", (void *)(pointer_to_ten + 6));

  // void* is a generic pointer; it must be cast before dereferencing
  void *generic_ptr = &ten;
  *(int *)generic_ptr = 30;
  /*
  NULL pointers:
  The integer constant 0 is implicitly cast to NULL (often defined as (void*)0).
  Assigning 0 to a pointer sets all its bits to zero (4 bytes on 32-bit,
  8 bytes on 64-bit platforms).
  */
  int *zero_ptr = 0;
  int *null_ptr = NULL;
  /*
  Pointer to pointer (int**, void**):
  Since a pointer is a variable stored in memory, we can take its address.
  Multiple levels of indirection are possible (e.g., int****), though two
  levels usually suffice for most purposes.

  Common use case:
  Organizing non-contiguous memory locations into a single collection using
  an array of pointers. Note: taking the address of a literal (e.g., &10)
  is invalid; we must point to variables instead.
  */
  int twenty = 20;
  int fifty = 50;
  int hundred = 100;
  int two_hundred = 200;
  // all e,f,g,h are stored somewhere in memory
  // but we can keep pointer to them 1 after another as array
  int *ptr_array[] = {&twenty, &fifty, &hundred, &two_hundred};
  /*
  Double pointers (e.g., int**, void**) store the address of another pointer.
  While int** is restricted to pointing to int*, void** acts as a generic
  pointer to any pointer type. Pointer arithmetic is consistent across double
  pointers because the size of a pointer is fixed (typically 4 or 8 bytes).
  */
  int **double_ptr = ptr_array;
  printf("First value via double pointer: %d\n", **double_ptr);
  printf("Second value via arithmetic: %d\n", **(double_ptr + 1));

  void **generic_double_ptr = (void **)ptr_array;
  // Dereferencing void** requires casting back to the specific pointer type
  printf("Value via generic double pointer: %d\n",
         **(int **)generic_double_ptr);
}

// TODO: function pointer
int add(int a, int b) { return a + b; }

void function_pointers() {
  // Syntax: return_type (*pointer_name)(parameter_types)
  int (*op)(int, int) = add;

  // Calling the function through the pointer
  int result = op(10, 20);
  printf("Result from function pointer: %d\n", result);
}

/*
problem with the pointers
1. pointer not initialized and being dereffed
2. all pointers can be NULL but not handled NULL case and being dereffed even in
function args
3. pointer arithmetic - *(ptr + n) can change a memory location where it should
not
4. string design is very bad in c - if '\0' i.e. NULL character is not there
finding size if infinite loop in c
5. implicit conversion of integers to pointer is bad design
6. no restriction on pointer to pointer conversion brings lot of problems if not
done correctly
7. returning pointer to stack memory and dereffing later when memory is cleaned
up is very bad
8. heap memory allocated and ptr to it is on stack and goes out of scope -
memory leak
9. data race when two thread have ptr to same memory and trying to write to that
memory together
10. void* is given to be used as generic in c - that's pretty useless to use
*/
int *return_pointer_to_stack() {
  int ten = 10;
  int *pointer_to_ten = &ten;
  return pointer_to_ten;
}

void simple_function(int a) {}

void pointer_problems() {
  // 1. pointer not initialized and being dereffed
  int *ptr_not_initialized;  // not initialized
  *ptr_not_initialized = 10; // dereffed

  // 2. all pointers can be NULL but not handled NULL case and being dereffed
  // even in function args
  int *null_pointer = NULL;
  *null_pointer = 10; // NULL pointer dereffed

  // 3. pointer arithmetic - *(ptr + n) can change a memory location where it
  // should not
  int ten = 10;
  int *pointer_to_ten = &ten;
  pointer_to_ten[1] = 10; // accessing memory this pointer should not have

  // 4. string design is very bad in c - if '\0' i.e. NULL character is not
  // there finding size if infinite loop in c
  char *string_array =
      "String"; // how to make it without null byte - c slaps one by default
  for (int i = 0; i < 10; i++) {
    if (string_array[i] ==
        '\0') { // this will never be true if string doesn't have the null byte
      puts("fount null byte");
      break;
    }
  }
  // 5. implicit conversion of integers to pointer is bad design
  int *implicit_int_to_pointer =
      0;        // assigned to NULL due to implicit conversion is good use
  int *h = ten; // int assigned by mistake in place of taking pointer using &
                // may not be traceable in code many times and cause bugs

  // 6. no restriction on pointer to pointer conversion brings lot of problems
  // if not done correctly say a function pointer in c casted into int* and
  // corrupted the function
  void (*function_pointer)(int);
  function_pointer = simple_function;
  int *int_pointer =
      (int *)function_pointer; // casting function pointer to int pointer type
  *int_pointer = 10;           // corrupting functions initial 4 bytes
  // 7. returning pointer to stack memory and dereffing later when memory is
  // cleaned up is very bad
  int *stack_return_value = return_pointer_to_stack();
  *stack_return_value = 10; // bad news

  // 8. heap memory allocated and ptr to it is on stack and goes out of scope -
  // memory leak
  int *heap_memory =
      malloc(10 * sizeof(int)); // k wil be gone after this function but not
                                // heap memory - memory leak
  // TODO: data race
  // 10. void* is given to be used as generic in c - that's pretty useless to
  // use
}

int main() { ptr_basics(); }
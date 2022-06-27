#include <stdio.h>
#include <stdlib.h>

void ptr_basics() {
  // create
  int ten = 10;
  int *pointer_to_ten = &ten;
  // int *b1 = &10;    //this is not possible in c - as c does not allow taking literal address
  //it should have been allowed by temporary putting memory on stack and giving pointer to it

  // deref
  *pointer_to_ten = 20;

  // pointer arithmetic - array is born from this
  printf("%p\n", pointer_to_ten);
  // adding 2 to ptr will move it here by 4*2 bytes
  printf("%p\n", pointer_to_ten + 2);
  // similarly adding 6 will move 4*6
  printf("%p\n", pointer_to_ten + 6);

  // void* - generic types are created using void* in c but explicit cast required as no type info is stored separately
  // but when deref is used we need to cast
  // i don't see any void* uses people use MACRO for such requirement - most uses in malloc memory allocation and giving pointer to it
  void *ptr_ten = &ten;
  // if deref is required cast to to some typed pointer type - it is user's responsibility to cast to valid type
  *(int *)ptr_ten = 30;
  /*
  NULL
  0 is implicitly casted to NULL - some do define as (void*)0
  eventually this means if we assign 0 to pointer all 4/8 bytes(based on
  platform 32/64 bit) of pointer are filled with 0 bits 
  00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 = on 64 bit platform
  */
  int *zero = 0;
  /*
  int**, void**
  take the pointer to pointer
  since pointer has also stored somewhere in memory we can take pointer to it
  we can even go further like int**** a and deref like ****a
  usually two levels i.e. pointer to pointer serves all purposes

  best use:
  so think as i have 4 memories at 4 different location i.e. they do not come 1
  after other for e.g. memory location is as = 10 50 100 200 we can still make
  them using ** pointer to be together as arrays of pointer 
  int* a[] = {&10,&50,&100,&200} - why address to literal is not allowed
  */
  int twenty = 20;
  int fifty = 50;
  int hundred = 100;
  int two_hundred = 200;
  // all e,f,g,h are stored somewhere in memory
  // but we can keep pointer to them 1 after another as array
  int *ptr_array[] = {&twenty, &fifty, &hundred, &two_hundred};
  /*
  void**
  this will mean we can keep pointer of arrays but these pointer can be to any
  type int** restricts that all pointer should be of memory to int* only (i.e.
  ints) since now we know these double pointers keep array of memory we can
  allow pointer arithmetic on void** or int** cause they will move by either 4/8
  only
  */
}

// TODO: function pointer

/*
problem with the pointers
1. pointer not initialized and being dereffed
2. all pointers can be NULL but not handled NULL case and being dereffed even in function args
3. pointer arithmetic - *(ptr + n) can change a memory location where it should not
4. string design is very bad in c - if '\0' i.e. NULL character is not there finding size if infinite loop in c
5. implicit conversion of integers to pointer is bad design
6. no restriction on pointer to pointer conversion brings lot of problems if not done correctly
7. returning pointer to stack memory and dereffing later when memory is cleaned up is very bad
8. heap memory allocated and ptr to it is on stack and goes out of scope - memory leak
9. data race when two thread have ptr to same memory and trying to write to that memory together
10. void* is given to be used as generic in c - that's pretty useless to use
*/
int* return_pointer_to_stack(){
  int ten = 10;
  int* pointer_to_ten = &ten;
  return pointer_to_ten;
}

void simple_function(int a){

}

void pointer_problems(){
  // 1. pointer not initialized and being dereffed
  int *ptr_not_initialized;   //not initialized
  *ptr_not_initialized = 10;  //dereffed 

  //2. all pointers can be NULL but not handled NULL case and being dereffed even in function args
  int *null_pointer = NULL;
  *null_pointer = 10;  //NULL pointer dereffed 

  //3. pointer arithmetic - *(ptr + n) can change a memory location where it should not
  int ten = 10;
  int *pointer_to_ten = &ten;
  pointer_to_ten[1] = 10;  //accessing memory this pointer should not have

  //4. string design is very bad in c - if '\0' i.e. NULL character is not there finding size if infinite loop in c
  char *string_array = "String";   //how to make it without null byte - c slaps one by default
  for (int i = 0; i <10; i++) {
    if(string_array[i] == '\0'){   //this will never be true if string doesn't have the null byte
      puts("fount null byte");
      break;
    }
  }
  //5. implicit conversion of integers to pointer is bad design
  int *implicit_int_to_pointer = 0;   //assigned to NULL due to implicit conversion is good use
  int *h = ten;   //int assigned by mistake in place of taking pointer using & may not be traceable in code many times and cause bugs

  //6. no restriction on pointer to pointer conversion brings lot of problems if not done correctly
  //say a function pointer in c casted into int* and corrupted the function 
  void (*function_pointer) (int);
  function_pointer = simple_function;
  int *int_pointer = (int *) function_pointer;  //casting function pointer to int pointer type
  *int_pointer = 10;  //corrupting functions initial 4 bytes
  //7. returning pointer to stack memory and dereffing later when memory is cleaned up is very bad
  int *stack_return_value = return_pointer_to_stack();
  *stack_return_value = 10;  //bad news

  //8. heap memory allocated and ptr to it is on stack and goes out of scope - memory leak
  int *heap_memory = malloc(10*sizeof(int));  //k wil be gone after this function but not heap memory - memory leak
  //TODO: data race
  //10. void* is given to be used as generic in c - that's pretty useless to use
}

int main() { ptr_basics(); }
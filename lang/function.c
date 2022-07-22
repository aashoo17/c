#include <stdio.h>
#include <stdlib.h>

// function

/*
function argument and return
arguments passed in c function gets copied and sent to function so original
value can never be modified this way unless we are returning back the value and
assigning it to the same variable which was passed as argument
*/
int function_arg_ret(int arg1, int arg2) {
  int c = arg1 + arg2;
  return c;
}

/*
pointer as arg
pointers gets copied and passed to function but as pointer work on addresses
they still can modify the original value of the variable pointers are always 4/8
bytes and copying them is easy they also avoid copying of bigger size data which
can itself take many cpu cycles

problems with the pointers in arg:
1. all pointers can possibly be NULL and hence it is required that all pointer
are checked for NULL before using them otherwise any dereference to them will
cause segmentation fault

*/
void function_ptr_arg(int *ptr) {
  if (ptr != NULL) {
    *ptr = *ptr + 1;
  }
}

/*
pointer return from functions
1. pointer to stack variable is returned - this pointer will be used later when
stack memory is freed and can corrupt memory when other variable is stored here
2. pointer to heap memory is returned - this pointer can be used without problem
but freeing that memory is the responsibility of the caller when left and not
freed will cause memory leak
3. pointer to argument of function is returned - this pointer can be used
without problem till the lifetime of arguments but later it will cause problem
as will try to modify the freed value
*/
int *function_heap_ptr_ret() {
  int *ptr = malloc(sizeof(int));
  *ptr = 10;
  return ptr;
}

int *function_stack_ptr_ret() {
  int local;         // local variable is stored in stack
  int *ptr = &local; // pointer to local variable is taken
  *ptr = 10;
  return ptr; // pointer to local/stack variable is returned
}

int *function_arg_ptr_ret(int local) { return &local; }

int *outer_function() {
  int local = 10;
  int *ret = function_arg_ptr_ret(local);
  return ret;
  // local variable is freed here (i.e. its lifetime is over here) and ret
  // variable which si returned still will point to this address dereffing it
  // will cause segmentation fault
}

// recursive functions
int factorial(int n) {
  if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}

//prototype of function
void prototype();

int main() {
  // calling function
  int a = 10;
  // arg a can only be modified if return value of function is assigned to it
  a = function_arg_ret(a, 20);
}

//implementation of function prototype
void prototype() {
  printf("prototype\n");
}
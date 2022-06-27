#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
allocation on stack in linux is also method calls - alloca()
int a[10]; syntax simplifies that for you by calling that function implicitly
*/

void array() {
  // create x on stack and x is pointer to first element
  int int_array[] = {1, 2, 3, 4};

  // modify
  int_array[0] = 10;
  *(int_array + 1) = 20;    //equal to a[1]

  // read
  int b = int_array[1];
  // designated initializers
  // 3rd elm put to 10 and others will be made 0
  int designated_initializer[10] = {[3] = 10};

  /*function with array syntax vs pointer syntax are same for c
  int sum(int *ar, int n);
  int sum(int *, int);
  int sum(int ar[], int n);
  int sum(int [], int);
  */

  // const
  const int const_array[] = {1};
  // what is the problem here says double const is used
  // is one const is enough to make this array non modifiable
  // const int const b[] = {2};

  // tell the differences
  int e = 30;
  const int *f = &e;       // pointer can not modify underlying memory here
  int *const g = &e;       // pointer can not be reassigned to another address
  const int *const h = &e; // pointer neither can modify the underlying value or
                           // can be assigned to another memory address

  // heap based array
  size_t size = 5;
  int *i = malloc(sizeof(int) * size);
  for (size_t j = 0; j < size; j++) {
    i[j] = 10 + j;
  }
}

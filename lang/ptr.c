#include <stdio.h>
/*
ptr creation
ptr deref
ptr arithmetic
void*
NULL
int**, void** etc
*/

void ptr_basics() {
  // create
  int a = 10;
  int *b = &a;
  // int *b1 = &10;    //this is not possible in c - as c does not allow taking
  // literal address
  //it should have been allowed by temporary putting memory on stack and giving pointer to it

  // deref
  *b = 20;

  // pointer arithmetic - array is born from this
  printf("%p\n", b);
  // adding 2 to ptr will move it here by 4*2 bytes
  printf("%p\n", b + 2);
  // similarly adding 6 will move 4*6
  printf("%p\n", b + 6);

  // void* - generic types are created using void* in c but explicit cast required as no type info is stored seperately
  // but when deref is used we need to cast
  // i don't see any void* uses people use MACRO for such requirement
  void *c = &a;
  // if deref is required cast to to some typed pointer type - it is user's responsibility to cast to valid type
  *(int *)c = 30;
  /*
  NULL
  0 is NULL - some do define as (void*)0
  eventually this means if we assign 0 to pointer all 4/8 bytes(based on
  platform 32/64 bit) of pointer are filled with 0 bits 00000000 00000000
  00000000 00000000 00000000 00000000 00000000 00000000 = on 64 bit platform
  */
  int *d = 0;
  /*
  int**, void**
  take the pointer to pointer
  since pointer has also stored somewhere in memory we can take pointer to it
  we can even go further like int**** a and deref like ****a
  usually two levels i.e. pointer to pointer serves all purposes

  best use:
  so think as i have 4 memories at 4 different location i.e. they do not come 1
  after other for e.g. memory location is as = 10 50 100 200 we can still make
  them using ** pointer to be together as arrays of pointer int* a[] =
  {&10,&50,&100,&200} - why address to literal is not allowed
  */
  int e = 10;
  int f = 50;
  int g = 100;
  int h = 200;
  // all e,f,g,h are stored somewhere in memory
  // but we can keep pointer to them 1 after another as array
  int *i[] = {&e, &f, &g, &h};
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

int main() { ptr_basics(); }
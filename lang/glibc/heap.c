#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void print(int *a,size_t size) {
  assert(a != NULL);
  for (size_t i = 0; i < size; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int main() {
  // allocates memory - no initialization
  int *a = malloc(sizeof(int) * 10); // malloc
  print(a,10);
  // allocates memory - initializes it to zero
  int *b = calloc(10, sizeof(int)); // calloc
  print(b,10);
  // reallocates memory
  int *c = realloc(b, sizeof(int) * 5); // realloc
  print(c,5);
  free(c); // free heap memory
  free(a);
}
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void print(int *a) {
  assert(a != NULL);
  for (size_t i = 0; i < 10; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int main() {
  // allocates memory - no initialization
  int *a = malloc(sizeof(int) * 10); // malloc
  print(a);
  // allocates memory - initializes it to zero
  int *b = calloc(10, sizeof(int)); // calloc
  print(b);
  // reallocates memory
  int *c = realloc(b, sizeof(int) * 5); // realloc
  print(c);
  free(c); // free heap memory
  free(a);
}
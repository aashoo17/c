#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h> //string functions

// string functions
void string_functions() {
  // strcpy(), strlen(), strcmp(), strcat()
  char a[] = "Hello World";
  char b[50];

  strcpy(b, a);
  puts(b);
  // this will show difference between strlen() and sizeof()
  printf("%ld %ld\n", strlen(b), sizeof(b));
  printf("%d\n", strcmp(b, a)); // comparison
  strcat(b, a);                 // concat
  puts(b);
}

static void print(unsigned char *a, size_t size) {
  assert(a != NULL);
  for (size_t i = 0; i < size; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

// mem functions
void mem_functions() {
  // memcpy(), memcmp(), memset(),memmove()
  unsigned char a[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // byte array
  unsigned char b[50];
  memcpy(b, a, sizeof(a));
  // sizeof(a) is given as sizeof(b) will be unnecessary long with garbage value
  print(b, sizeof(a));
  printf("%d\n", memcmp(b, a, sizeof(a)));
  // get length
  size_t len = sizeof(a);
  // this should be used when memory is overlapped by two variables, though
  // works if not overlapped too
  memmove(b, a, len);
  print(b, len);
  memset(b, 81, len);
  print(b, len);
}

int main() { mem_functions(); }

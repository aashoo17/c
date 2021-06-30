#include <stdio.h>

int main() {
  int a = 10;
  int i = 0;

  // while loop
  while (i++ < 10) {
    printf("%d ", i);
  }
  // for loop
  for (size_t i = 0; i < 10; i++) {
    printf("%lu ", i);
  }
}
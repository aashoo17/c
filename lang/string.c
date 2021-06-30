#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_basics() {
  // string - array of characters
  // allocation on stack
  char a[] = "Hello World"; // we can write as {'H','e','l'.......,'\0'} also

  // use string functions to operate on them
  // strcpy
  char b[100];
  strcpy(b, a);
  printf("%s\n", b);

  // strlen
  printf("%ld\n", strlen(a));

  // strcmp
  printf("%d\n", strcmp(b, a));

  // strcat
  strcat(b, a);
  printf("%s\n", b);

  // all possible string types
  // stack based
  char c[] = "Some string";

  // heap allocation
  char *d = malloc(100);
  strcpy(d, "Hello String on heap");
  // non modifiable - stored in executable binary (for read only)
  char *e = "Hello there";
}
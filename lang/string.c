#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_basics() {
  // 1. Stack Allocation (Mutable)
  // 'a' is an array of characters initialized with a string literal.
  // It is stored on the stack and can be modified.
  char a[] = "Hello World";
  printf("Original string a: %s\n", a);

  // 2. Safe String Copying
  // 'b' is a fixed-size buffer. We must ensure we don't overflow it.
  // Using a predefined constant or sizeof ensure we match the buffer size.
  char b[100];

  // Unsafe: strcpy(b, a); - Vulnerable to buffer overflow if 'a' > 100 chars
  // Safer: snprintf guarantees null-termination and checks bounds.
  snprintf(b, sizeof(b), "%s", a);
  printf("Copied string b: %s\n", b);

  // 3. String Length
  // strlen returns size_t (unsigned long), safe to print with %zu
  printf("Length of a: %zu\n", strlen(a));

  // 4. String Comparison
  // strcmp returns 0 if equal, <0 if b < a, >0 if b > a
  if (strcmp(b, a) == 0) {
    printf("Strings a and b are identical.\n");
  } else {
    printf("Strings a and b are different.\n");
  }

  // 5. Safe String Concatenation
  // Unsafe: strcat(b, a); - Risk of overflow if b doesn't have enough space
  // Safer: Check remaining space
  size_t current_len = strlen(b);
  size_t append_len = strlen(a);
  size_t buffer_size = sizeof(b);

  if (current_len + append_len < buffer_size) {
    strncat(b, a, buffer_size - current_len - 1);
    printf("Concatenated string b: %s\n", b);
  } else {
    printf("Not enough space to concatenate!\n");
  }

  // 6. Heap Allocation (Dynamic)
  // Useful when size isn't known at compile time or for large strings.
  char *d = malloc(100 * sizeof(char));
  if (d == NULL) {
    perror("Failed to allocate memory");
    return;
  }

  // Safe copy to heap memory
  snprintf(d, 100, "Hello String on heap");
  printf("Heap string d: %s\n", d);

  // 7. Read-Only Strings (String Literals)
  // 'e' points to a string literal, usually stored in read-only memory text
  // segment. Attempting to modify *e (e.g., e[0] = 'h') causes undefined
  // behavior (segfault).
  const char *e = "Hello there";
  printf("Read-only string e: %s\n", e);

  // Cleanup
  free(d);
}

int main() {
  string_basics();
  return 0;
}
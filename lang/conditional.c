#include <stdbool.h> // C99 standard for booleans
#include <stdio.h>

/*
TRUTHINESS IN C:
- False: 0, NULL, '\0' (null character)
- True: Anything else (including negative numbers and "" empty strings!)

Note: In C, string literals like "" are pointers to memory, so they are non-zero
(True).
*/

void check_truthiness() {
  // 1. Integer Truthiness
  int a = 10;
  if (a) { // Implicit check: equivalent to if (a != 0)
    printf("a (%d) is True\n", a);
  }

  int zero = 0;
  if (!zero) {
    printf("zero (%d) is False\n", zero);
  }

  // 2. String/Pointer Truthiness
  char *str = "";
  if (str) {
    // This prints because 'str' points to a valid memory address
    printf("Empty string \"\" is True (it's a valid pointer: %p)\n",
           (void *)str);
  }

  char *null_ptr = NULL;
  if (!null_ptr) {
    printf("NULL pointer is False\n");
  }
}

void switch_example() {
  int b = 20;

  switch (b) {
  case 10:
    printf("Value is 10\n");
    break;
  case 20:
    printf("Value is 20\n");
    // Fallthrough example (omitting break intentionally would execute next
    // case)
    break;
  case 30:
    printf("Value is 30\n");
    break;
  default:
    printf("Value is unknown (default)\n");
    break;
  }
}

void ternary_operator() {
  int age = 18;
  // (condition) ? value_if_true : value_if_false
  const char *status = (age >= 18) ? "Adult" : "Minor";
  printf("Age %d is: %s\n", age, status);
}

int main() {
  check_truthiness();
  switch_example();
  ternary_operator();

  return 0;
}
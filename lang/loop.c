#include <stdbool.h>
#include <stdio.h>

void while_loop_demo() {
  printf("--- While Loop ---\n");
  int count = 0;
  // Standard while loop
  while (count < 5) {
    printf("%d ", count);
    count++;
  }
  printf("\n");

  // While with post-increment in condition (common C idiom)
  // Be careful: variable use inside the loop reflects the incremented value if
  // done this way? actually: (i++ < 5) uses old value for check, then
  // increments.
  int i = 0;
  printf("Compact while: ");
  while (i++ < 5) {
    // i is already 1 here on first iteration
    printf("%d ", i);
  }
  printf("\n");
}

void do_while_demo() {
  printf("\n--- Do-While Loop ---\n");
  // Guaranteed to run at least once
  int val = 100;
  do {
    printf("This runs once even if condition is false (val: %d)\n", val);
  } while (val < 10);
}

void for_loop_demo() {
  printf("\n--- For Loop ---\n");
  // C99 allowed declarations inside for loop head
  for (int i = 0; i < 5; i++) {
    printf("%d ", i);
  }
  printf("\n");

  // Multiple variables in loop head
  printf("Multiple variables: ");
  for (int i = 0, j = 10; i < 3; i++, j--) {
    printf("(%d, %d) ", i, j);
  }
  printf("\n");
}

void flow_control_demo() {
  printf("\n--- Break and Continue ---\n");
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      continue; // Skip even numbers
    }
    if (i > 7) {
      break; // Stop completely when > 7
    }
    printf("%d ", i);
  }
  printf("\n");
}

void infinite_loop_demo() {
  printf("\n--- Infinite Loop (Simulated) ---\n");
  int safety_counter = 0;

  // commonly used infinite loops: while(1) or for(;;)
  while (true) {
    printf(".");
    safety_counter++;
    if (safety_counter >= 10) {
      printf(" Broken by safety check");
      break;
    }
  }
  printf("\n");
}

int main() {
  while_loop_demo();
  do_while_demo();
  for_loop_demo();
  flow_control_demo();
  infinite_loop_demo();
  return 0;
}
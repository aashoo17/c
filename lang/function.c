#include <stdio.h>
#include <stdlib.h>

// --- Prototypes ---
void pass_by_value_demo();
void pass_by_reference_demo();
void return_pointers_demo();
void static_variable_demo();
void recursion_demo();

/*
 1. PASS BY VALUE
 Arguments are copied into the function parameter.
 Changing 'a' inside does NOT affect the caller's 'a'.
*/
void modify_value(int a) {
  a = a + 10;
  printf("  Inside modify_value: a = %d\n", a);
}

void pass_by_value_demo() {
  printf("\n--- Buy Value ---\n");
  int x = 5;
  printf("  Before: x = %d\n", x);
  modify_value(x);
  printf("  After:  x = %d (Unchanged)\n", x);
}

/*
 2. PASS BY REFERENCE (via Pointers)
 We pass the address of variables.
 Changing '*ptr' modifies the ACTUAL variable in the caller.
*/
void modify_reference(int *ptr) {
  if (ptr != NULL) {
    *ptr = *ptr + 10;
    printf("  Inside modify_reference: *ptr = %d\n", *ptr);
  }
}

void pass_by_reference_demo() {
  printf("\n--- Pass By Reference (Pointer) ---\n");
  int y = 5;
  printf("  Before: y = %d\n", y);
  modify_reference(&y);
  printf("  After:  y = %d (Modified)\n", y);
}

/*
 3. RETURNING POINTERS
*/
// SAFE: Returning pointer to HEAP memory
int *get_heap_int(int value) {
  int *p = malloc(sizeof(int));
  if (p)
    *p = value;
  return p;
}

// UNSAFE: Returning pointer to STACK memory
// (Modern compilers warn about this: "function returns address of local
// variable")
int *get_stack_int_bad() {
  int local = 42;
  return &local; // DANGEROUS: 'local' is destroyed when function returns!
}

void return_pointers_demo() {
  printf("\n--- Returning Pointers ---\n");

  // Heap example
  int *heap_ptr = get_heap_int(100);
  if (heap_ptr) {
    printf("  Heap int: %d\n", *heap_ptr);
    free(heap_ptr); // Caller is responsible for cleanup
  }

  // Stack example (Do not dereference in real code!)
  int *bad_ptr = get_stack_int_bad();
  printf("  Stack ptr returned: %p (Dangling - accessing this is Undefined "
         "Behavior)\n",
         (void *)bad_ptr);
}

/*
 4. STATIC VARIABLES
 Static variables in functions retain their value between calls.
 They are initialized only once.
*/
void count_calls() {
  static int count = 0;
  count++;
  printf("  Call number: %d\n", count);
}

void static_variable_demo() {
  printf("\n--- Static Variables ---\n");
  count_calls();
  count_calls();
  count_calls();
}

/*
 5. RECURSION
 Function calling itself. Must have a base case.
*/
int factorial(int n) {
  if (n <= 1)
    return 1;
  return n * factorial(n - 1);
}

void recursion_demo() {
  printf("\n--- Recursion ---\n");
  int n = 5;
  printf("  Factorial of %d is %d\n", n, factorial(n));
}

int main() {
  pass_by_value_demo();
  pass_by_reference_demo();
  return_pointers_demo();
  static_variable_demo();
  recursion_demo();
  return 0;
}
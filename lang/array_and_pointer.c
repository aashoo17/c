#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void array_declaration_initialization() {
  printf("\n--- Array Declaration & Initialization ---\n");

  // 1. Declaration
  int int_array_ten[10];

  // 2. Initialization element-by-element
  int_array_ten[0] = 10;
  int_array_ten[1] = 20;
  printf("Element 0: %d, Element 1: %d\n", int_array_ten[0], int_array_ten[1]);

  // 3. Declaration and initialization together
  int literal_initialized_array[] = {10, 20, 30, 40, 50};
  size_t size = sizeof(literal_initialized_array) / sizeof(int);
  printf("Literal initialized size: %zu\n", size);

  // 4. Designated initializer (C99 feature)
  // Useful for sparse data.
  // This sets index 10 to 100, and all previous indices (0-9) to 0 implicitly.
  int designated_initialized_array[11] = {[10] = 100};
  printf("Designated [0]: %d, [10]: %d\n", designated_initialized_array[0],
         designated_initialized_array[10]);

  // Why can't we do assignment?
  // int d[5];
  // d = {1, 2, 3}; // COMPILER ERROR
  // ANSWER: Arrays are second-class citizens in C assignment. The array name
  // 'd' decays to a constant pointer to the first element. You cannot change
  // where 'd' points. To copy arrays, you must use memcpy or a loop.
}

/*
 PRECEDENCE RULES DEMO

 Operators:
 ++ (Prefix increment) : Right-to-Left
 *  (Dereference)      : Right-to-Left
 ++ (Postfix increment): Left-to-Right (highest precedence)

 Common pointer idioms:
 *ptr++   : Dereference ptr, THEN increment ptr (results in value at old ptr)
 *++ptr   : Increment ptr, THEN dereference (results in value at new ptr)
 ++*ptr   : Dereference ptr, THEN increment the VALUE (results in old val + 1)
*/

void unary_operator_precedence() {
  printf("\n--- Unary Operator Precedence ---\n");

  // We use malloc so we have a mutable pointer 'p'
  // (Array names like 'arr' are constant pointers and cannot be incremented)
  int *p = malloc(sizeof(int) * 5);
  if (!p)
    return;

  p[0] = 10;
  p[1] = 20;
  p[2] = 30;

  int *start = p; // Keep original to free later

  printf("Start address: %p, Value: %d\n", p, *p);

  // CASE 1: *++p
  // Precedence: ++ (prefix) and * (deref) are same level, associativity
  // Right-to-Left.
  // 1. ++p happens first (p now points to index 1)
  // 2. * dereferences the new p
  int val1 = *++p;
  printf("After *++p: Value = %d (Expected 20), p is now at index 1\n", val1);
  assert(val1 == 20);

  // CASE 2: *p++
  // Postfix ++ has higher precedence than *.
  // 1. p++ happens (pointer increments), but the expression result is the OLD
  // pointer.
  // 2. * dereferences the OLD pointer.
  // Reset p to index 1 just to be clear
  // p is currently at index 1 (20).
  int val2 = *p++;
  printf("After *p++: Value = %d (Expected 20), p is now at index 2\n", val2);
  assert(val2 == 20);
  // p is indeed at index 2 now (30)
  printf("Current *p: %d (Expected 30)\n", *p);

  free(start);
}

// ARRAYS AS ARGUMENTS
// Arrays "decay" into pointers when passed to functions.
// 'arr' is just a pointer here. sizeof(arr) = 8 (on 64-bit).
// You MUST pass size separately.
void print_array(int *arr, int size) {
  printf("Array contents: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

/*
 Pointer to array vs Array of pointers
 int *arr[10] -> Array of 10 pointers to int
 int (*arr)[10] -> Pointer to an array of 10 ints
*/
void advanced_declarations() {
  printf("\n--- Advanced Declarations ---\n");
  int arr[10];
  int *ptr_to_arr_elem = arr;         // Points to arr[0] (int*)
  int(*ptr_to_entire_arr)[10] = &arr; // Points to entire array (int(*)[10])

  printf("ptr_to_arr_elem: %p\n", (void *)ptr_to_arr_elem);
  printf("ptr_to_entire_arr: %p\n", (void *)ptr_to_entire_arr);

  // Incrementing behaves differently!
  // ptr_to_arr_elem + 1 adds sizeof(int) (4 bytes)
  // ptr_to_entire_arr + 1 adds sizeof(int[10]) (40 bytes)
  printf("ptr_to_arr_elem + 1: %p (diff: %ld)\n", (void *)(ptr_to_arr_elem + 1),
         (long)(ptr_to_arr_elem + 1) - (long)ptr_to_arr_elem);
  printf("ptr_to_entire_arr + 1: %p (diff: %ld)\n",
         (void *)(ptr_to_entire_arr + 1),
         (long)(ptr_to_entire_arr + 1) - (long)ptr_to_entire_arr);
}

int main() {
  array_declaration_initialization();
  unary_operator_precedence();

  printf("\n--- Array Arguments ---\n");
  int data[] = {1, 2, 3, 4, 5};
  print_array(data, 5);

  advanced_declarations();

  return 0;
}
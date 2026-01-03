#include <stdio.h>
#include <stdlib.h>

void basic_stack_array() {
  printf("\n--- Stack Array & Initialization ---\n");
  // Standard initialization
  int arr[] = {10, 20, 30, 40};

  // Calculate size in elements
  size_t count = sizeof(arr) / sizeof(arr[0]);
  printf("Elements: %zu, Total Size: %zu bytes\n", count, sizeof(arr));

  // Designated Initializers (C99): useful for sparse arrays
  // Initialize index 3 to 100, others default to 0
  int sparse[10] = {[3] = 100, [8] = 200};
  printf("Sparse[3]: %d, Sparse[0]: %d\n", sparse[3], sparse[0]);
}

void pointer_arithmetic() {
  printf("\n--- Pointer Arithmetic ---\n");
  int arr[] = {100, 200, 300};

  // Array name acts like a pointer to the first element
  printf("arr[0]: %d\n", arr[0]);
  printf("*arr:   %d\n", *arr);

  // Accessing index 1
  printf("arr[1]: %d\n", arr[1]);
  printf("*(arr + 1): %d\n",
         *(arr + 1)); // Pointer addition adds sizeof(int) bytes
}

// Function showing Array Decay
// Even though declared as int arr[10], it decays to int *arr
void print_array_size(int arr[10]) {
  // Warning: sizeof(arr) here is size of pointer (8 bytes on 64-bit), not 40
  // bytes!
  printf(
      "  Inside function: sizeof(arr) = %zu (Pointer size, not Array size!)\n",
      sizeof(arr));
}

void array_decay_demo() {
  printf("\n--- Array Decay ---\n");
  int arr[10];
  printf("  In main scope:   sizeof(arr) = %zu\n", sizeof(arr));
  print_array_size(arr);
}

void heap_array() {
  printf("\n--- Heap Allocation ---\n");
  size_t size = 5;

  // Allocate memory for 5 integers
  int *heap_arr = malloc(size * sizeof(int));
  if (heap_arr == NULL) {
    perror("Malloc failed");
    return;
  }

  // Use like a normal array
  for (size_t i = 0; i < size; i++) {
    heap_arr[i] = (i + 1) * 11;
  }

  printf("Heap Array: ");
  for (size_t i = 0; i < size; i++) {
    printf("%d ", heap_arr[i]);
  }
  printf("\n");

  // Important: Free memory
  free(heap_arr);
}

void const_correctness() {
  printf("\n--- Const Pointers vs Const Data ---\n");
  int val = 10;
  int other = 20;

  // 1. Pointer to CONST int (Data is read-only)
  const int *ptr_to_const = &val;
  // *ptr_to_const = 15; // Error: Cannot modify value
  ptr_to_const = &other; // OK: Can point to something else
  printf("const int *: Can change target, but not value.\n");

  // 2. CONST Pointer to int (Pointer address is fixed)
  int *const const_ptr = &val;
  *const_ptr = 15; // OK: Can modify value
  // const_ptr = &other; // Error: Cannot change target
  printf("int *const: Can change value, but not target. New val: %d\n",
         *const_ptr);

  // 3. CONST Pointer to CONST int (Locked down)
  const int *const locked = &val;
  // *locked = 30; // Error
  // locked = &other; // Error
  printf("const int *const: Cannot change value OR target.\n");
}

int main() {
  basic_stack_array();
  pointer_arithmetic();
  array_decay_demo();
  heap_array();
  const_correctness();
  return 0;
}

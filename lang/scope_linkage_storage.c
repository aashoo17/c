#include <stdio.h>
#include <stdlib.h>

/*
 1. LINKAGE (Visibility across files)
 - External Linkage (Default for globals): Visible to other translation units
 (.c files).
 - Internal Linkage ('static' global): Visible ONLY in this file.
*/
int g_external_var =
    100; // Can be accessed in other files using 'extern int g_external_var;'
static int g_internal_var = 50; // Hidden from other files.

/*
 2. STORAGE DURATION (Lifetime)
 - Static Storage: Exists for the entire program execution (Globals, static
 locals).
 - Automatic Storage: Exists only while the block is executing (Stack
 variables).
 - Allocated Storage: Exists until explicitly freed (Heap).
*/

void storage_duration_demo() {
  printf("\n--- Storage Duration ---\n");

  // Automatic variable (re-initialized every call)
  int auto_var = 1;

  // Static variable (initialized ONLY ONCE, persists value between calls)
  static int static_var = 1;

  printf("  auto_var: %d, static_var: %d\n", auto_var, static_var);

  auto_var++;
  static_var++;
}

/*
 3. SCOPE (Visibility within file)
 - File Scope: Visible from declaration to end of file.
 - Block Scope: Visible inside { ... }
 - Shadowing: Inner scope variables hide outer scope variables of the same name.
*/
int x = 1000; // File scope

void scope_shadowing_demo() {
  printf("\n--- Scope & Shadowing ---\n");
  printf("  File scope x: %d\n", x);

  int x = 10; // Block scope (Shadows global x)
  printf("  Function scope x: %d (Shadows global)\n", x);

  {
    int x = 5; // Inner block scope (Shadows function x)
    printf("  Inner block x: %d (Shadows function)\n", x);
  }

  printf("  Back to Function scope x: %d\n", x);

  // Access global x explicitly? C doesn't have ::x like C++,
  // but if we didn't shadow it, we could see it.
}

int main() {
  // Storage Demo: Call multiple times to see static variable increment
  storage_duration_demo();
  storage_duration_demo();
  storage_duration_demo();

  // Scope Demo
  scope_shadowing_demo();

  // Linkage/Global access
  printf("\n--- Globals ---\n");
  printf("  External Global: %d\n", g_external_var);
  printf("  Internal (Static) Global: %d\n", g_internal_var);

  return 0;
}
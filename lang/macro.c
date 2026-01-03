#include <stdio.h>

// 1. CONSTANTS
// Preprocessor constant: Text replacement. No type safety. No memory address.
#define BUFFER_SIZE 1024

// C Const: Typed variable. Has scope and memory address.
const int kBufferSize = 1024;

/*
 2. FUNCTION-LIKE MACROS & SAFETY
 Pitfall: Text substitution can mess up precedence.
 Solution: ALWAYS wrap arguments and the entire expression in parentheses.
*/
// UNSAFE: MAX_BAD(1 + 2, 3) expands to 1 + 2 > 3 ? 1 + 2 : 3 => 3 > 3? ...
// result is wrong if logic depends on grouping
#define MAX_BAD(a, b) a > b ? a : b

// SAFER: Parentheses protect widely.
// STILL RISKY: Side effects (e.g., MAX_SAFE(i++, j++)) double evaluate
// arguments!
#define MAX_SAFE(a, b) ((a) > (b) ? (a) : (b))

void macro_safety_demo() {
  printf("\n--- Macro Safety ---\n");
  int x = 2, y = 3;

  // Basic usage works
  printf("Max of %d, %d is %d\n", x, y, MAX_SAFE(x, y));

  // Precedence issue with unsafe macro
  // logical: 2 * MAX_BAD(2, 3) => 2 * 2 > 3 ? 2 : 3  => 4 > 3 ? 2 : 3 => Result
  // 2 (Wrong! Should be 2 * 3 = 6)
  int result_bad = 2 * MAX_BAD(2, 3);
  printf("2 * MAX_BAD(2, 3) gives: %d (Expected 6)\n", result_bad);

  int result_safe = 2 * MAX_SAFE(2, 3);
  printf("2 * MAX_SAFE(2, 3) gives: %d (Correct)\n", result_safe);

  // Side Effect Hazard
  int i = 5, j = 10;
  // Expands to: ((i++) > (j++) ? (i++) : (j++))
  // j incremented TWICE!
  int max_val = MAX_SAFE(i++, j++);
  printf("Side effect hazard: MAX(i++, j++) returned %d, j is now %d (Expected "
         "11)\n",
         max_val, j);
}

/*
 3. SPECIAL OPERATORS
 #  : Stringify (Convert argument to string literal)
 ## : Token Paste (Concatenate two tokens into one)
*/
#define STRINGIFY(x) #x
#define VAR_NAME(name, index) name##index

void special_operators_demo() {
  printf("\n--- # and ## Operators ---\n");

  printf("Stringified: %s\n", STRINGIFY(Hello World));

  int val1 = 100;
  int val2 = 200;
  // Expands to: printf("val1: %d\n", val1);
  printf("Value of val1: %d\n", VAR_NAME(val, 1));
  printf("Value of val2: %d\n", VAR_NAME(val, 2));
}

/*
 4. MULTI-LINE MACROS
 Use do-while(0) to swallow the semicolon and create a single block scope.
*/
#define LOG_ERROR(msg)                                                         \
  do {                                                                         \
    fprintf(stderr, "[ERROR] %s: %s\n", __func__, msg);                        \
  } while (0)

void multi_line_demo() {
  printf("\n--- Multi-line Macro ---\n");
  if (1)
    LOG_ERROR("Something failed (simulated)");
  else
    printf("This else usage is safe due to do-while(0)\n");
}

/*
 5. PREDEFINED MACROS
*/
void predefined_info() {
  printf("\n--- Predefined Macros ---\n");
  printf("Date: %s\n", __DATE__);
  printf("Time: %s\n", __TIME__);
  printf("File: %s\n", __FILE__);
  printf("Line: %d\n", __LINE__);
  printf("Standard C: %d\n", __STDC__);
}

/*
 6. CONDITIONAL COMPILATION
 Used for platform specific code or feature toggles.
*/
#define FEATURE_ENABLED 1

void conditional_compilation() {
  printf("\n--- Conditional Compilation ---\n");
#if defined(FEATURE_ENABLED) && FEATURE_ENABLED > 0
  printf("Feature is ENABLED\n");
#else
  printf("Feature is DISABLED\n");
#endif
}

int main() {
  macro_safety_demo();
  special_operators_demo();
  multi_line_demo();
  predefined_info();
  conditional_compilation();
  return 0;
}
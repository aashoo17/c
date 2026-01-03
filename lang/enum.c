#include <stdio.h>

/*
 1. BASIC ENUM
 Enums in C are essentially named integer constants.
 By default, values start at 0 and increment by 1.

 Issue: Enum members are in the global/file scope (not scoped to the enum type).
 Solution: Use a prefix (e.g., GENDER_...) to avoid name collisions.
*/
enum Gender {
  GENDER_MALE,   // 0
  GENDER_FEMALE, // 1
  GENDER_OTHER   // 2
};

void basic_enum_demo() {
  printf("\n--- Basic Enum ---\n");
  enum Gender g = GENDER_MALE;
  printf("Gender value: %d\n", g);

  if (g == GENDER_MALE) {
    printf("It is a Male.\n");
  }
}

/*
 2. CUSTOM VALUES
 You can assign specific integer values. Unassigned ones continue the sequence.
*/
enum Status {
  STATUS_OK = 200,
  STATUS_BAD_REQUEST = 400,
  STATUS_UNAUTHORIZED, // 401
  STATUS_SERVER_ERROR = 500
};

void custom_values_demo() {
  printf("\n--- Custom Values ---\n");
  printf("STATUS_OK: %d\n", STATUS_OK);
  printf("STATUS_UNAUTHORIZED: %d (Previous + 1)\n", STATUS_UNAUTHORIZED);
}

/*
 3. TYPEDEF ENUM & SWITCH
 Typedef makes it cleaner to use (no 'enum' keyword needed).
 best practice: Use enums with switch statements to handle all cases.
*/
typedef enum { COLOR_RED, COLOR_GREEN, COLOR_BLUE } Color;

void print_color(Color c) {
  printf("\n--- Switch on Enum ---\n");
  switch (c) {
  case COLOR_RED:
    printf("Color is RED\n");
    break;
  case COLOR_GREEN:
    printf("Color is GREEN\n");
    break;
  case COLOR_BLUE:
    printf("Color is BLUE\n");
    break;
  default:
    printf("Unknown Color\n");
  }
}

/*
 4. TYPE SAFETY (LACK THEREOF)
 C Enums are just integers. You can assign any int to an enum variable,
 even if it's not one of the defined constants. This is different from C++.
*/
void integer_equivalence_demo() {
  printf("\n--- Integer Equivalence ---\n");
  Color c = 100; // Compiles fine in C (Warning in C++)
  printf("Assigned 100 to Color enum: %d\n", c);

  // They can be used in arithmetic
  int result = GENDER_MALE + STATUS_OK;
  printf("Math with enums: %d + %d = %d\n", GENDER_MALE, STATUS_OK, result);
}

int main() {
  basic_enum_demo();
  custom_values_demo();
  print_color(COLOR_GREEN);
  integer_equivalence_demo();
  return 0;
}

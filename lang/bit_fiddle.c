#include <stdint.h>
#include <stdio.h>

// Helper to print binary representation of a number (8 bits for simplicity)
void print_binary(const char *label, int num) {
  printf("%-20s: %3d (0x%02X) => ", label, num, num);
  for (int i = 7; i >= 0; i--) {
    printf("%c", (num & (1 << i)) ? '1' : '0');
    if (i == 4)
      printf(" "); // Space nip for readability
  }
  printf("\n");
}

void bit_operators() {
  printf("\n--- Basic Bitwise Operators ---\n");
  int a = 10; // 0000 1010
  int b = 6;  // 0000 0110

  print_binary("a", a);
  print_binary("b", b);

  print_binary("a | b (OR)", a | b);     // 1110 (14)
  print_binary("a & b (AND)", a & b);    // 0010 (2)
  print_binary("a ^ b (XOR)", a ^ b);    // 1100 (12)
  print_binary("~a (NOT)", (uint8_t)~a); // Inverts bits

  printf("\n--- Shifts ---\n");
  print_binary("a << 2 (Left)", a << 2);  // 0010 1000 (40)
  print_binary("a >> 1 (Right)", a >> 1); // 0000 0101 (5)
}

void common_tricks() {
  printf("\n--- Common Bit Tricks ---\n");
  int val = 0b00001010; // 10
  int pos = 2;          // 0-indexed position (3rd bit)

  print_binary("Original", val);

  // 1. SET BIT (OR with 1 at pos)
  int set = val | (1 << 0); // Set bit 0
  print_binary("Set bit 0", set);

  // 2. CLEAR BIT (AND with NOT 1 at pos)
  int clear = val & ~(1 << 3); // Clear bit 3 (which is 1)
  print_binary("Clear bit 3", clear);

  // 3. TOGGLE BIT (XOR with 1 at pos)
  int toggle = val ^ (1 << 2); // Toggle bit 2
  print_binary("Toggle bit 2", toggle);

  // 4. CHECK BIT
  int is_set = (val & (1 << 3));
  printf("Is bit 3 set? %s\n", is_set ? "YES" : "NO");
}

/*
 BIT FIELDS:
 Bit fields allow packing multiple variables into a single byte/word.
 Useful for hardware registers, network protocols, or memory constrained
 systems.
*/
typedef struct {
  // : N specifies width in bits
  unsigned int age : 4;    // Max val: 15 (1111)
  unsigned int active : 1; // Boolean flag (0 or 1)
  unsigned int tier : 2;   // Max val: 3 (11)
} UserStatus;

void bit_field_demo() {
  printf("\n--- Bit Fields ---\n");
  printf("Size of UserStatus: %zu bytes (packed into int)\n",
         sizeof(UserStatus));
  // Note: sizeof is typically 4 (size of int) despite using fewer bits,
  // unless packed attribute is used, but padding rules apply.

  UserStatus u = {0};
  u.age = 10; // 1010 fits in 4 bits
  u.active = 1;
  u.tier = 3; // 11 fits in 2 bits

  printf("Age: %d, Active: %d, Tier: %d\n", u.age, u.active, u.tier);

  // Overflow/Truncation Demo
  printf("Assigning 20 to age (max 15)...\n");
  u.age = 20; // 10100 (5 bits) -> Truncates to lower 4 bits: 0100 (4)
  printf("New Age: %d (Truncated!)\n", u.age);
}

int main() {
  bit_operators();
  common_tricks();
  bit_field_demo();
  return 0;
}
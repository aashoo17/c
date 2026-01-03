#include <float.h> // for float constants
#include <inttypes.h> //this includes stdint.h by default so we may skip including stdint.h it
#include <limits.h>  // for int constants
#include <stdbool.h> // for bool constants
#include <stdio.h>   // for printf

void integer() {
  // signed integers
  signed char a = 10; // at least 8 bits
  short b = 10;       // at least 16 bits
  int c = 10;         // at least 16 bits, typically 32
  long d = 10L;       // at least 32 bits
  long long e = 10LL; // at least 64 bits

  // unsigned integers
  unsigned char f = 10U;        // at least 8 bits
  unsigned short g = 10U;       // at least 16 bits
  unsigned h = 10U;             // at least 16 bits, typically 32
  unsigned long i = 10UL;       // at least 32 bits
  unsigned long long j = 10ULL; // at least 64 bits

  // hexadecimal, octal, and binary literals
  int k = 0x10;   // hexadecimal
  int l = 010;    // octal
  int m = 0b1010; // binary
}

// fixed integers types
void fixed_integer_types() {
  // signed fixed-width types
  int8_t a = 10;  // 1 byte
  int16_t b = 10; // 2 bytes
  int32_t c = 10; // 4 bytes
  int64_t d = 10; // 8 bytes

  // unsigned fixed-width types
  uint8_t e = 10;  // 1 byte
  uint16_t f = 10; // 2 bytes
  uint32_t g = 10; // 4 bytes
  uint64_t h = 10; // 8 bytes

  // pointer-sized integer types
  intptr_t i = (intptr_t)&a;
  uintptr_t j = (uintptr_t)&a;

  // TODO: using inttypes.h with stdint.h types
  // all the fixed type are typedeffed and can vary based on platform how a user
  // will know which formatting char to be used PRId32 macro makes it easy to do
  // so
  printf("%" PRId32 "%" PRIdPTR, c, i);
}

void explicit_conversion() {
  double d = 10.9;
  // explicit conversion (casting) truncates the fractional part
  int n = (int)d; // n is 10

  // casting to a smaller integer type (potential data loss or wrap-around)
  int i = 257;
  uint8_t b = (uint8_t)i; // b is 1 (257 % 256)
}

void implicit_conversion() {
  // integer promotion: types smaller than int are promoted to int
  short a = 10;
  int b = a; // implicit conversion of short to int

  // usual arithmetic conversions: lower rank types are converted to higher rank
  int c = 5;
  double d = 2.5;
  double result = c + d; // c is implicitly converted to double

  // potential issues: signed to unsigned comparison
  int i = -1;
  unsigned int j = 1;
  // i is converted to unsigned int, becoming a very large value
  bool is_less = (i < j); // false because -1 becomes a large unsigned value
}

void float_types() {
  float a = 10.0f;       // single precision - 32 bits
  double b = 10.0;       // double precision - 64 bits
  long double c = 10.0L; // extended precision - typically 80 or 128 bits
}

void bool_types() {
  // bool, true, and false are macros defined in stdbool.h
  bool a = true;
  bool b = false;

  // _Bool is the underlying primitive type introduced in C99
  _Bool c = 1;

  // Booleans are essentially integers; any non-zero value assigned to a bool
  // becomes 1
  bool d = 42; // d is 1 (true)
}

void overflow() {
  // signed integer overflow: Undefined Behavior
  int a = INT_MAX;
  int b = a + 1;

  // unsigned integer overflow: Well-defined wrap-around
  unsigned int c = UINT_MAX;
  unsigned int d = c + 1;

  // floating point overflow: typically results in infinity
  float e = FLT_MAX * 2.0f;
  // floating point underflow: results in 0 or a subnormal number
  float f = FLT_MIN / 1e10f;

  printf("Float overflow: %f\n", (double)e);
  printf("Float underflow: %e\n", (double)f);
}
void char_types() {
  char a = 'A';  // Character literals are integers (ASCII 65)
  char b = '\0'; // Null byte, used to terminate strings
  char c = 0;    // Integer 0 is implicitly converted to to '\0'

  /*
   * 'char' can be signed or unsigned depending on the compiler and platform.
   * This affects arithmetic and values > 127 (outside standard ASCII).
   */
  signed char sc = 127;
  unsigned char uc = 255;

  // On x86 architectures, 'char' is typically signed by default.
  // On ARM and PowerPC, 'char' is often unsigned by default.
  // Platform-dependent behavior for values > 127

  // If char is unsigned, 255 is stored as is else it is stored as -1
  char d = 255;
}

void printing() {
  int a = 10;
  float b = 10.1f;
  char c = 'A';
  bool d = true;

  // printf is a variadic function, not a macro.
  printf("%04d %06.2f %c %d\n", a, b, c, d);
}

// other types like - pointer, struct, union, enum etc.. will be covered
// separately

int main() { overflow(); }

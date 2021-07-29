#include <inttypes.h> //this includes stdint.h by default so we may skip including stdint.h it
#include <stdbool.h>
#include <stdio.h>

/*
integer min sizes - for portability
implcit integer conversion rule
TODO: why L, LL, UL, ULL etc is used
by default things are of int size (32 bit in x64) and later implicit coversion
will happen this is fine if only literal like 10 is used long a = 10; 32 bit 10
will get converted to 64 bit later what if we used this long a = 10 *
10000000000000000 * 100000000;  // a multiplication which overflows for 32 bit
size but not for 64 bit multiplication will happen result stored in 32 bit (a
some bit last as 32 bit is not enough to store) and later implicitly converted
to 64 bit

if we used like
long a = 10L * 10000000000000000 * 100000000;
compiler will see it like - long * int * int
and convert all int into long of size 64 bit and after multiplication result is
also stored in 64 bit
*/

void integer() {
  // signed integers
  //todo: see the c standard for sizes of int types
  signed char a = 10; // char - 1 byte
  short b = 10;       // short - 2 byte
  int c = 10;         // int - min 2 byte
  long d = 10L;       // long - min 4 byte
  long long e = 10LL; // long long - min 8 byte

  // unsigned counter parts
  unsigned char f = 10;
  unsigned short g = 10;
  unsigned int h = 10; // unsigned int and unsigned are same type
  unsigned long i = 10UL;
  unsigned long long j = 10ULL;

  // octal, hexadecimal and binary
  int k = 0x10;
  int l = 010;    //octal could have been taken prefixed with 0o would have been uniform with hex & binary
  int m = 0b01010;
}

// fixed integers types
void fixed_integer_types() {
  // signed types
  int8_t a = 10;
  int16_t b = 10;
  int32_t c = 10;
  int64_t d = 10;

  // unsigned types
  uint8_t e = 10;
  uint16_t f = 10;
  uint32_t g = 10;
  uint64_t h = 10;

  // enough to store pointer size - 32/64 bit based on platform
  uintptr_t i = (uintptr_t)&a;

  // TODO: using inttypes.h with stdint.h types
  //all the fixed type are typedeffed and can vary based on platform how a user will know which formatting char to be used
  //PRId32 macro makes it easy to do so
  printf("%" PRId32 "%ld", a, i);
}

void explicit_conversion() {
  float d = 10.1;
  // explicit integer conversion
  int n = (int)d;
}

// TODO: tell about all the implicit conversions allowed in c
void implicit_conversion() {}

void float_types() {
  float a = 10;  // single precision - 32 bit
  double b = 10; // double precision - 64 bit
}

void bool_types() {
  // using stdbool
  bool a = true;
  bool b = false;

  // if stdbool.h is not used
  _Bool c = true;
}

/*
char:
ascii at C's core - representing chars as integers
how can unicode can be used in c (especially utf-8)
what is null byte in char
*/
void char_types() {
  char a = 'A';
  char b = '\0'; // null byte
  char c = 0;    // null byte - 0 in ascii is '\0' 
}

/*
printing integer, float, char, bool types
*/
void printing() {
  int a = 10;
  float b = 10.1;
  char c = 'A';
  bool d = true;

  // how printf is variadic - is it macro or function
  printf("%04d %06.2f %c %d\n", a, b, c, d);
}

// other types like - pointer, struct, union, enum etc.. will be covered
// seperately

int main() { fixed_integer_types(); }

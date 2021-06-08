#include <inttypes.h> //this includes stdint.h by default so we may skip including stdint.h it
#include <stdbool.h>
#include <stdio.h>

/*
integer min sizes - for portability
implcit integer conversion rule
TODO: why L, LL, UL, ULL etc is used
*/

void integer()
{
  // signed integers
  signed char a = 10; // char - 1 byte
  short b = 10;       // short - 2 byte
  int c = 10;         // int - min 2 byte
  long d = 10L;       // long - min 4 byte
  long long e = 10LL; // long long - min 8 byte

  // unsigned counter parts
  unsigned char f = 10;
  unsigned short g = 10;
  unsigned h = 10; // unsigned int and unsigned are same type
  unsigned long i = 10UL;
  unsigned long long j = 10ULL;

  // octal, hexadecimal and binary
  int k = 0x10;
  int l = 010;
  int m = 0b01010;
}

// fixed integers types
void fixed_integer_types()
{
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
  printf("%" PRId32 "%ld", a, i);
}

void explicit_conversion()
{
  float d = 10.1;
  // explicit integer conversion
  int n = (int)d;
}

//TODO: implicit conversion in c
void implicit_conversion()
{
}

void float_types()
{
  float a = 10;  //single precision
  double b = 10; //double precision
}

void bool_types()
{
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
void char_types()
{
  char a = 'A';
  char b = '\0'; //null byte
}

/*
printing integer, float, char, bool types
*/
void printing()
{
  int a = 10;
  float b = 10.1;
  char c = 'A';
  bool d = true;

  // how printf is variadic - is it macro or function
  printf("%04d %06.2f %c %d\n", a, b, c, d);
}

//other types like - pointer, struct, union, enum etc.. will be covered seperately

int main() { fixed_integer_types(); }

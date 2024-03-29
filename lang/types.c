#include <inttypes.h> //this includes stdint.h by default so we may skip including stdint.h it
#include <stdbool.h>
#include <stdio.h>

void integer() {
  // signed integers
  // todo: see the c standard for sizes of int types
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
  int l = 010; // octal could have been taken prefixed with 0o would have been
               // uniform with hex & binary
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
  // all the fixed type are typedeffed and can vary based on platform how a user
  // will know which formatting char to be used PRId32 macro makes it easy to do
  // so
  printf("%" PRId32 "%ld", a, i);
}

void explicit_conversion() {
  float d = 10.1;
  // explicit integer conversion
  int n = (int)d;
}

// TODO: tell about all the implicit conversions allowed in c
// TODO: problem with implicit conversions
void implicit_conversion() {
  short a = 10;
  int b = a; // implicit conversion of short to int
}

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
//integer & float overflow
void overflow() {
  // signed integer overflow
  int a = 2147483647;
  int b = a + 1;

  // unsigned integer overflow
  unsigned int c = 4294967295;
  unsigned int d = c + 1;

  // float overflow
  float e = 3.4028e+338;    //infinity is printed to mark overflow
  float f = 3.1e-338;          //underflow
  printf("%f\n",e);
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
  char c = 0; // null byte - integer 0 is implicitly converted to null byte in
              // ascii which is '\0'

  // TODO: char and int problem in c
  /*
  char is internally signed char or unsigned char depending on the platform
  though bit pattern will match with ascii for both signed and unsigned char
  any integer operation or conversion to char will create problem due to signed
  or unsigned char
  */
  // TODO: show that overflow wrapping value vs 2's complement will be different
  // so that we can say signed/unsigned char will create problem though we still
  // can say overflow may be platform dependent and we can not rely on it if
  // both are same
  char d = 255; // if signed char is used then it can not contain 255 and
                // overflow will happen
  printf("%c\n", d); // this does not print anything as it points to non
                     // printable character
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
// separately

int main() { overflow(); }

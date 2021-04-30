/*
integers:
representation of integer in binary form:
why 2's complement is used for negative no
how processor knows if we are adding signed nos or unsigned nos
do they use different opcode for signed/unsigned types
or 2's complement is such that adding/substracting them when signed types are there
and when unsigned types are there processor yields same result which works for both
for e.g.
10 and -10 in binary are in 2's complement 00000110 & 11111010
adding them will result in 0 in binary i should get  00000000
if 00000110 & 11111010 and both were unsigned 10 and ....some other value... and adding them processor gives back 00000000 (i.e. zero)
it is not possible naa so how signed/unsigned operation differ at processor level

integer overflow:
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

/*
integer min sizes - for portability
implcit integer conversion rule
TODO: why L, LL, UL, ULL etc is used
*/

void integer() {
  //signed integers
  signed char a = 10; // char - 1 byte
  short b = 10;       // short - 2 byte
  int c = 10;         // int - min 2 byte
  long d = 10L;       // long - min 4 byte
  long long e = 10LL; // long long - min 8 byte

  // unsigned counter parts
  unsigned char f = 10;
  unsigned short g = 10;
  unsigned int h = 10;
  unsigned long i = 10UL;
  unsigned long long j = 10ULL;

  //octal, hexadecimal and binary
  int k = 0x10;
  int l = 010;
  int m = 0b01010;

  //explicit integer conversion
  int n = (int)d;
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
  uintptr_t i = 10;

  //TODO: using inttypes.h with stdint.h types
  printf("%"PRId32,a);
}

// floats
void float_types() {
  float a = 10;
  double b = 10;
}

// bools
void bool_types() {
  bool a = true;
  bool b = false;

  //if stdbool is not used
  _Bool c = true;
}

// chars
void char_types() {
  char a = 'A';
  char b = '\0';
}

//printing integer, float, char, bool types
void print(){
  int a = 10;
  printf("%04d\n",a);
  float b = 10.1;
  printf("%06.2f\n",b);
  char c = 'A';
  printf("%c\n",c);
  bool d = true;
  printf("%d\n",d);
}

int main(){
  print();
}

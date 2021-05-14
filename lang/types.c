/*
what does it mean to have types like int,float,char...etc processor doesn't have meaning of type
why concept of signed and unsigned 
int a = 10;  => see the assembly code what does it mean for processor
all the basic c types does not allow aliasing when assigned they do explicit copy so they allow one owner only except for pointer
but we know processor only supports memory address in RAM through MAR (memory address register) so how variables are designed over address/pointer

pointer give aliasing access same memory through multiple variables
*/

/*
TODO: move these topics in notes
integers:
representation of integer in binary form:
why 2's complement is used for negative no
how processor knows if we are adding signed nos or unsigned nos
do they use different opcode for signed/unsigned types
multiplication and divison has different opcode 
or 2's complement is such that adding/substracting them when signed types are there
and when unsigned types are there processor yields same result which works for both

integer overflow:
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h> //this includes stdint.h by default so we may skip borrowing it

/*
integer min sizes - for portability
implcit integer conversion rule
TODO: why L, LL, UL, ULL etc is used
*/

void integer()
{
  //signed integers
  signed char a = 10; // char - 1 byte
  short b = 10;       // short - 2 byte
  int c = 10;         // int - min 2 byte
  long d = 10L;       // long - min 4 byte
  long long e = 10LL; // long long - min 8 byte

  //unsigned counter parts
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
  uintptr_t i = 10;

  //TODO: using inttypes.h with stdint.h types
  printf("%" PRId32, a);
}

/*
floats:
how floats are represented at processor level - why IEEE-754 standard got most acceptance
all about float precison thing - why floats are not reflexive (a == a)
special registers for float operation 
why floats are not used in kernel usually
underflow, overflow, subnormal, NaN in floats
*/
void float_types()
{
  float a = 10;
  double b = 10;
}

/*
bool:
so C was not having bool at its core it was thought as 0 and 1 only
so ==, !=, < , <= , >, >= etc will return 0 or 1
even c allows something called truthy and falsy (welcome javascript) 
so bool need only a bit to represent but processor usually work with byte and then there is getting address - so how c handles it
whats up with _Bool (not bool used without stdbool.h)

*/
void bool_types()
{
  //using stdbool
  bool a = true;
  bool b = false;

  //if stdbool is not used
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
  char b = '\0';
}

//printing integer, float, char, bool types
void print()
{
  int a = 10;
  float b = 10.1;
  char c = 'A';
  bool d = true;

  //how printf is variadic - is it macro or function
  printf("%04d %06.2f %c %d\n", a, b, c, d);
}

int main()
{
  print();
}

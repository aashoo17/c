#include <stdio.h>

/*
enum in c become file scoped this is big problem
below Male can be accessed anywhere in the .c file
what will happen when I have a variable also name as Male somwhere in the file ??

cpp came with the solution to use enum class Gender{} like this - without breaking compatibility
*/

enum Gender {
  Male,  // assigned 0 implicitly
  Female // assigned 1 implicitly
};

enum Color { Red = 10, Green = 20, Blue = 30 };

int main() {
  enum Gender a;
  a = Male;

  enum Color b;
  b = Red;

  printf("%d\n", b);
}

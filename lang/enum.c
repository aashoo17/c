#include <stdio.h>

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

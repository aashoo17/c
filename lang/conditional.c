#include <stdio.h>

/*
false - 0, NULL, "", '\0',
true - except for false values are all true
*/
int main() {
  int a = 10;
  // if(a!= 0){} - //if(a){} would be same
  if (a != 0) {
    puts("got 10");
  } else
    puts("10 not received");
}
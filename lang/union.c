/*
union:
a type which can store multiple variables but only one at a time

union UN{
    char name[40];
    int age;
};

here UN union can have two things name and age which are of sizes 40 and 4 bytes
each since 40 is bigger it will allocate memory for 40 now in 40 bytes we any
time time store 4 byte int or 40 byte name its upto us

only problem union has that at any time what is stored we have to know
explicitly otherwise bytes will be stored for int and we are say using as char
array
*/
#include <stdio.h>
#include <string.h>

union UN {
  char name[40];
  int age;
};

// typedef union
typedef union UN UN;

int main() {
  union UN u;
  u.age = 20;

  // now here we are knowing that int age is stored inside the union using it as
  // char array will lead to some kind of error later
  printf("%d\n", u.age);
  // now char array is being stored
  strcpy(u.name, "Some name");
  // use the union for anything char array can be use for
  printf("%s\n", u.name);
}
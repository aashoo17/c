#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure declaration
struct Human {
  char name[100];
  int age;
};

// typedef struct
typedef struct Human Human;

// initialize struct
void create_initialize() {
  // on stack memory
  struct Human h;
  // access fields
  strcpy(h.name, "Some Random Name");
  h.age = 20;

  // allocation on heap and initialization
  struct Human *h1 = malloc(sizeof(struct Human));
  // access fields from pointer
  strcpy(h1->name, "Another name");
  h1->age = 20;

  // using struct literal for initialization
  struct Human h2 = {"some name", 20};
  // struct literal out of order initialization
  struct Human h3 = {.age = 20, .name = "Some name"};

  // pointer to struct
  struct Human *h4 = &h2;

  //static allocation - stored in static memory part of the process
  static struct Human h5;

  // heap cleanup
  free(h1);
}

// accessing members
void access_struct_members() {
  // stack allocation
  Human a;
  a.age = 10;
  strcpy(a.name, "Some Name");

  // heap allocation
  Human *b = malloc(sizeof(Human));
  b->age = 20;
  strcpy(b->name, "Some Name");
}

// structure assignment
void struct_assignment() {
  struct Human a;
  struct Human b = {"Some Name", 10};

  // for arrays assignment is not possible but we can do for struct
  a = b;  //this assigns each field wise
}

// passing struct around in functions as pointer and as value
// using pointer to change a struct
void change_struct(struct Human *h) {
  assert(h != NULL);
  strcpy(h->name, "Some other changed name");
  h->age = 20;
}

// passing pointer as read only
// struct which will be passed may not be const
// const in function argument says that function can not modify underlying data
void read_only_struct(const struct Human *h) {
  // get the age in another variable
  int a = h->age;
  // h->age = 100; i.e. changing the value of struct Human will not be possible
  // through const pointer
}

/*
following steps are required
way to change a struct without passing pointer
1. pass the struct as copy/by value in function
2. modify the struct inside function
3. return this struct from function
4. assign this returned function to previous struct to change the values
*/

struct Human change_struct_without_pointer(struct Human h) {
  strcpy(h.name, "Some other changed name");
  h.age = 20;
  return h;
}

// array of struct
void array_of_struct() {
  struct Human a[100];

  // accessing members
  a[0].age = 10; // so [] has higher precedence than .
  strcpy(a[0].name, "Some Name");

  printf("%lu\n", sizeof(a));
}

/*
flexible array member in struct
last member will be array but size not given so it is flexible can be as big as
required later so stack allocation will not allocate any memory for this
flexible array field so we have to use heap allocation through malloc only for
it to work
*/
struct flex {
  int count;
  double avg;
  double scores[]; // size for this array may be omitted
};

// doing allocation for flexible array
void flex_allocation() {
  // allocated 10 double extra memory which will be used for scores field
  struct flex *f = malloc(sizeof(struct flex) + sizeof(double) * 10);
  // now access scores and fill them
  f->scores[2] = 10.0;
}

// TODO: ways to store structure in file with portability

int main() { struct_assignment(); }
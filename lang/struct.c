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
  printf("\n--- Create & Initialize ---\n");
  // on stack memory
  struct Human h;
  // access fields
  snprintf(h.name, sizeof(h.name), "Stack Human");
  h.age = 20;
  printf("Stack: %s, %d\n", h.name, h.age);

  // allocation on heap and initialization
  struct Human *h1 = malloc(sizeof(struct Human));
  if (h1 == NULL) {
    perror("Malloc failed");
    return;
  }
  // access fields from pointer
  snprintf(h1->name, sizeof(h1->name), "Heap Human");
  h1->age = 21;
  printf("Heap: %s, %d\n", h1->name, h1->age);

  // using struct literal for initialization
  struct Human h2 = {"Literal Human", 22};
  printf("Literal: %s, %d\n", h2.name, h2.age);

  // struct literal out of order initialization (Designated Initializers - C99)
  struct Human h3 = {.age = 23, .name = "Designated Human"};
  printf("Designated: %s, %d\n", h3.name, h3.age);

  // pointer to struct
  struct Human *h4 = &h2;
  printf("Pointer to struct: %s\n", h4->name);

  // static allocation - stored in static memory part of the process
  // Zero initialized by default
  static struct Human h5;
  printf("Static (default initialized): %s (age: %d)\n", h5.name, h5.age);

  // heap cleanup
  free(h1);
}

// accessing members
void access_struct_members() {
  printf("\n--- Access Struct Members ---\n");
  // stack allocation
  Human a;
  a.age = 10;
  snprintf(a.name, sizeof(a.name), "Alice");

  // heap allocation
  Human *b = malloc(sizeof(Human));
  if (b) {
    b->age = 20;
    snprintf(b->name, sizeof(b->name), "Bob");
    printf("Access: %s is %d, %s is %d\n", a.name, a.age, b->name, b->age);
    free(b);
  }
}

// structure assignment
void struct_assignment() {
  printf("\n--- Struct Assignment ---\n");
  struct Human a;
  struct Human b = {"Source Name", 99};

  // For arrays assignment is not possible directly, but structs are copied by
  // value (all bytes)
  a = b; // This performs a deep copy of the struct fields

  printf("Copied struct 'a': %s, %d\n", a.name, a.age);

  // Verify independence
  snprintf(b.name, sizeof(b.name), "Changed Source");
  printf("After modifying source 'b':\n  a: %s\n  b: %s\n", a.name, b.name);
}

// passing struct around in functions as pointer and as value
// using pointer to change a struct
void change_struct(struct Human *h) {
  assert(h != NULL);
  snprintf(h->name, sizeof(h->name), "Pointer Changed Name");
  h->age = 30;
}

// passing pointer as read only
// const in function argument says that function can not modify underlying data
void read_only_struct(const struct Human *h) {
  // get the age in another variable
  int a = h->age;
  printf("Read only view: %s is %d\n", h->name, a);
  // h->age = 100; // Compile error: assignment of member 'age' in read-only
  // object
}

/*
way to change a struct without passing pointer
1. pass the struct as copy/by value in function
2. modify the struct inside function
3. return this struct from function
4. assign this returned function to previous struct to change the values
*/
struct Human change_struct_without_pointer(struct Human h) {
  snprintf(h.name, sizeof(h.name), "Returned Value Name");
  h.age = 40;
  return h;
}

void struct_function_demo() {
  printf("\n--- Structs and Functions ---\n");
  Human h = {"Original", 10};

  change_struct(&h);
  printf("After change_struct(&h): %s\n", h.name);

  read_only_struct(&h);

  h = change_struct_without_pointer(h);
  printf("After change_struct_without_pointer(h): %s\n", h.name);
}

// array of struct
void array_of_struct() {
  printf("\n--- Array of Structs ---\n");
  struct Human humans[2];

  // accessing members
  humans[0].age = 10;
  snprintf(humans[0].name, sizeof(humans[0].name), "Array Human 0");

  humans[1] = (struct Human){"Array Human 1", 11};

  printf("Array size in bytes: %lu\n", sizeof(humans));
  for (int i = 0; i < 2; i++) {
    printf("Index %d: %s\n", i, humans[i].name);
  }
}

/*
flexible array member in struct (C99 feature)
last member will be array but size not given.
Important:
1. Must be the last member.
2. Struct must have at least one other named member.
3. Cannot be directly on stack (size is unknown), use malloc.
*/
struct flex {
  int count;
  double avg;
  double scores[]; // Flexible array member
};

// doing allocation for flexible array
void flex_allocation() {
  printf("\n--- Flexible Array Member ---\n");
  int num_scores = 5;
  // Allocation: struct base size + size for array elements
  struct flex *f = malloc(sizeof(struct flex) + sizeof(double) * num_scores);
  if (f == NULL)
    return;

  f->count = num_scores;
  f->avg = 0.0;

  printf("Flexible struct usage:\n");
  for (int i = 0; i < num_scores; i++) {
    f->scores[i] = (i + 1) * 1.1;
    printf("  Score[%d] = %.2f\n", i, f->scores[i]);
  }

  free(f);
}

// TODO: Serialization - writing/reading structs to files
// Note: Direct binary write of structs (fwrite(&h, sizeof(h), ...)) is
// non-portable due to endianness and padding/alignment differences between
// architectures.

int main() {
  create_initialize();
  access_struct_members();
  struct_assignment();
  struct_function_demo();
  array_of_struct();
  flex_allocation();
  return 0;
}
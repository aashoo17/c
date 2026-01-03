#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
 UNION BASICS:
 A union is a custom data type where all members share the SAME memory location.
 The size of the union is determined by its largest member.
 Only one member can contain a valid value at any given time.
*/

union Data {
  int i;
  float f;
  char str[20];
};

void basic_usage() {
  printf("\n--- Basic Union Usage ---\n");
  union Data data;

  printf("Memory size occupied by union Data: %lu bytes\n", sizeof(data));

  // 1. Store an integer
  data.i = 10;
  printf("data.i : %d\n", data.i);

  // 2. Store a float (overwrites the integer)
  data.f = 220.5;
  printf("data.f : %.1f\n", data.f);
  // Reading 'i' now produces garbage (reinterpretation of float bits as int)
  printf("data.i (after setting f) : %d (Garbage/Reinterpreted)\n", data.i);

  // 3. Store a string (overwrites the float)
  snprintf(data.str, sizeof(data.str), "C Programming");
  printf("data.str : %s\n", data.str);
}

/*
 MEMORY OVERLAP DEMO:
 Because they share memory, unions allow "type punning" - viewing the same bits
 as different types. Useful for low-level byte inspection.
*/
union Register {
  uint32_t full_reg;
  struct {
    uint8_t byte0;
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
  } bytes; // Anonymous struct inside union
};

void memory_overlap() {
  printf("\n--- Memory Overlap / Type Punning ---\n");
  union Register r;
  r.full_reg = 0xDEADBEEF;

  printf("Full Register Value: 0x%X\n", r.full_reg);
  // Note: Byte order depends on Endianness (Little Endian vs Big Endian)
  printf("Bytes: [0x%X, 0x%X, 0x%X, 0x%X]\n", r.bytes.byte0, r.bytes.byte1,
         r.bytes.byte2, r.bytes.byte3);
}

/*
 TAGGED UNION (SAFE USAGE):
 Since C doesn't track which field is active, we wrap the union in a struct
 alongside a "tag" (enum) to track type safety manually.
*/
typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_STRING } Tag;

typedef struct {
  Tag type;
  union {
    int i;
    float f;
    char str[20];
  } data;
} ValidatedValue;

void print_value(ValidatedValue v) {
  printf("Value: ");
  switch (v.type) {
  case TYPE_INT:
    printf("%d (int)\n", v.data.i);
    break;
  case TYPE_FLOAT:
    printf("%.2f (float)\n", v.data.f);
    break;
  case TYPE_STRING:
    printf("'%s' (string)\n", v.data.str);
    break;
  default:
    printf("Unknown type\n");
  }
}

void tagged_union_demo() {
  printf("\n--- Tagged Union (Safe Usage) ---\n");

  ValidatedValue v1;
  v1.type = TYPE_INT;
  v1.data.i = 42;
  print_value(v1);

  ValidatedValue v2;
  v2.type = TYPE_STRING;
  snprintf(v2.data.str, sizeof(v2.data.str), "Safe Union");
  print_value(v2);
}

int main() {
  basic_usage();
  memory_overlap();
  tagged_union_demo();
  return 0;
}
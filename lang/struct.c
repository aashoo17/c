/*
struct: think of all small things we do with struct and write down
so in c variable are a way to find memory address of a data during code execution
struct is a way to give a name to more than 1 variables 

struct Human{
    int a;
    int b;
    int c;
    int d;
    int e;
};

so say i have allocated 20 bytes in memory with 5 ints of 4 bytes each
entire memory can be thought of as a single name say i give Human
all 5 memory address of interest now given name as a,b,c,d,e respectively

what we have to learn to do with struct

struct declaration
struct creation on stack and heap and 
its initialization using struct literal and struct member wise initialization
manipulating struct by passing it to function = as pointer and as copy

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure declaration
struct Human{
    char name[40];
    int age;
};

//passing struct around in functions as pointer and as copy/value

//using pointer to change a struct
void change_struct(struct Human *h){
    strcpy(h->name,"Some other changed name");
    h->age = 20;
}

//passing pointer as read only
void read_only_struct(const struct Human *h){
    //get the age in another variable
    int a = h->age;
    //h->age = 100; i.e. changing the value of struct Human will not be possible through const pointer
}

//way to change a struct without passing pointer

/*
following steps are required 
1. pass the struct as copy/by value in function
2. modify the copy struct
3. return this struct from function
4. assign this returned function to previous struct to change the values
*/

struct Human change_struct_without_pointer(struct Human h){
    strcpy(h.name,"Some other changed name");
    h.age = 20;

    return h;
}

//assign to previous struct in main

int main(){
    // use of structure allocating on stack
    struct Human h;
    strcpy(h.name,"Some Random Name");
    h.age = 20;

    //allocation on heap and initialization
    struct Human *h1 = malloc(sizeof(struct Human));
    strcpy(h1->name,"Another name");
    h1->age = 20;

    //using struct literal for initialization
    struct Human h2 = {"some name",20};
    //struct literal out of order initialization
    struct Human h3 = {.age = 20, .name = "Some name"};
}
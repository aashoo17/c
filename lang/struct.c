#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//structure declaration
struct Human{
    char name[100];
    int age;
};

//typedef struct
typedef struct Human Human;

//initialize struct
void initialize(){
    //struct initialization
    //use of structure allocating on stack
    struct Human h;
    //access fields
    strcpy(h.name, "Some Random Name");
    h.age = 20;

    //allocation on heap and initialization
    struct Human *h1 = malloc(sizeof(struct Human));
    //access fields
    strcpy(h1->name, "Another name");
    h1->age = 20;

    //using struct literal for initialization
    struct Human h2 = {"some name", 20};
    //struct literal out of order initialization
    struct Human h3 = {.age = 20, .name = "Some name"};

    //pointer to struct
    struct Human *h4 = &h2;
}

//accessing members
void access_struct_members(){
    //stack allocation
    Human a;
    a.age = 10;
    strcpy(a.name, "Some Name");

    //heap allocation
    Human *b = malloc(sizeof(Human));
    b->age = 20;
    strcpy(b->name, "Some Name");
}

//passing struct around in functions as pointer and as copy/value
//using pointer to change a struct
void change_struct(struct Human *h){
    assert(h != NULL);
    strcpy(h->name, "Some other changed name");
    h->age = 20;
}

//passing pointer as read only
//struct which will be passed may not be const
//const in function argument says that function can not modify underlying data
void read_only_struct(const struct Human *h){
    //get the age in another variable
    int a = h->age;
    //h->age = 100; i.e. changing the value of struct Human will not be possible through const pointer
}

/*
following steps are required 
way to change a struct without passing pointer
1. pass the struct as copy/by value in function
2. modify the copy struct
3. return this struct from function
4. assign this returned function to previous struct to change the values
*/

struct Human change_struct_without_pointer(struct Human h){
    strcpy(h.name, "Some other changed name");
    h.age = 20;
    return h;
}

/*
flexible array member in struct
last member will be array but size not given so it is flexible can be as big as required later
so stack allocation will not allocate any memory for this flexible array field
so we have to use heap allocation through malloc only for it to work
*/
struct flex{
    int count;
    double avg;
    double scores[]; //size for this array may be omitted
};

//doing allocation for flexible array
void flex_allocation(){
    //allocated 10 double extra memory which will be used for scores field
    struct flex *f = malloc(sizeof(struct flex) + sizeof(double) * 10);
    //now access scores and fill them
    f->scores[2] = 10.0;
}

int main(){
}
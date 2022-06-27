#include <stdlib.h>
/*
SCOPE:
1. block scope
2. function scope
3. function prototype scope
4. file scope
*/
void function_block(){
        int i = 0;
}

void block_scope(){
    //conditional
    int i = 0;
    if(i == 0){
        //create a new variable
        int if_scoped_var = 10; //this will available inside if block only
    }
    //loop
    for(int i = 0; i < 5; i++){     //this i variable created in for is available inside for block only
        i++;    //i not available after the for block
    }
    //function
    function_block();   //i created in function will not be available later
}

/*
linkage
1. internal linkage
2. external linkage
*/
//linkage in global or file scoped variables
static int internal_linkage_var = 10;   //internal linkage
//TODO: even if it is having external linkage we still can not use it in another file. how it can be done without extern use
int external_linkage_variable = 10;     //external linkage
//[external variable explained beautifully](https://www.youtube.com/watch?v=ySY_FlA7EvA)
extern int extern_var; //any same name variable in another translation unit/file initialized its value can be used here

void external_linkage_in_function(){}   //external linkage
static void internal_linkage_in_function(){}    //internal linkage

/*
storage class:
1. automatic storage
2. static/global storage
3. heap storage
*/
int global_storage = 10;    //global storage - lives till the lifetime of program
void storage_classes(){
    static int static_storage = 10;     //lives till the lifetime of program
    int automatic_storage = 10;     //gets cleaned when function exits 
    int *heap_storage = malloc(10);     //heap storage memory lives until freed explicitly
    free(heap_storage);
}
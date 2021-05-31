#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void array_declaration_initialization(){
    //declaration
    int a[10];
    float b[10];
    char c[100];

    //initialization
    a[0] = 10;
    a[1] = 20;

    //declaration and initialization together
    int d[] = {10,20,30,40,50};

    //designated initializer - this will let you initialize particular element even out of order
    //initialize 10th element as 100
    int e[] = {[10] = 100};

    //assignment of arrays
    //this is not possible to do like we can in initialization
    //TODO: why this is not done in c
    //d = {40,30,20,10,0}; 
}

//DO: learn about precedence order using Precedence.pdf in assets folder

//unary operator with same precedence used on same operand - so that associativity can be checked for unary ops
//e.g. things like *start++ over a pointer

void unary_operator_with_same_precedence(){
    //why int a[] = {10,20,...}; is not used here 
    //because then *++a can not be applied with error a is array type
    int *a = malloc(sizeof(int)*10);

    //print the pointer
    printf("%p\n",a);

    a[0] = 10;
    a[1] = 20;

    //now here * and ++ is unary operator applied on a, both are having same precedence and right to left associativity 
    //so first ++ is applied and then * 
    //that means first increment the pointer then deref it

    //this is same as *(a++)
    int b = *++a;
    //printing to see if pointer a moved by 4 address 
    printf("%p\n",a);

    //since ++ is prefix form a is incremented and assigned to b
    //if postfix is used b == 10 will be true
    assert(b == 20);
}



void passing_array_as_arg(){

}

void use_passing_array_function(){
    
}

int main(){

}
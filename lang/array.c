#include <stdio.h>
#include <stdlib.h>

void array()
{
    //create x on stack and x is pointer to first elm
    int a[] = {1, 2, 3, 4};

    //modify
    a[0] = 10;

    //read
    int b = a[1];
    //designated initializers
    //3rd elm put to 10 and others will be made 0
    int c[10] = {[3] = 10};

    /*function with array syntax vs pointer syntax are same for c
    int sum(int *ar, int n); 
    int sum(int *, int);
    int sum(int ar[], int n); 
    int sum(int [], int);
    */

    //const
    const int d[] = {1};
    //what is the problem here says double const is used
    //is one const is enough to make this array non modifiable
    //const int const b[] = {2};

    //tell the differences
    int e = 30;
    const int *f = &e;       //pointer can not modify underlying memory here
    int *const g = &e;       //pointer can not be reassigned to another address
    const int *const h = &e; //pointer neither can modify the underlying value or can be assigned to another memory address

    //heap based array
    int *i = malloc(sizeof(int) * 5);
    for (size_t j = 0; j < 5; j++)
    {
        i[j] = 10 + j;
    }
}

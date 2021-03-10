#include <stdio.h>
#include <stdlib.h> 

int main(){
    //create x on stack and x is pointer to first elm
    int x[] = {1,2,3,4};

    //modify 
    x[0] = 10;

    //read
    int y = x[1];
    //designated initializers
    //3rd elm put to 10 and others will be made 0
    int z[10] = {[3]=10}; 

    /*function with array syntax vs pointer syntax are same for c
    int sum(int *ar, int n); 
    int sum(int *, int);
    int sum(int ar[], int n); 
    int sum(int [], int);
    */
   
    //const
    const int a[] = {1};
    //what is the problem here says double const is used
    //is one const is enough to make this array non modifiable
    //const int const b[] = {2};

    //tell the differences
    int c = 30;
    const int *d = &c;
    int* const e = &c;
    const int* const f = &c;
}

#include<stdio.h>

/*
false - 0, NULL, "", '', 
true - except for false values are all true
*/
int main(){
    int a = 10;
    // a!= 0 and passing a in if is same
    if (a != 0)
        puts("got 10");
    else
        puts("10 not received");
}
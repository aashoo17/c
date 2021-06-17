/*
#define
1. define constant
2. define function like macro
TODO: #define vs const
one thing I know is const being variable can be scoped so same name const can be defined again in other scope
#define is visible in entire file

function like macro are replacement for functions as macros are inlined and if fuction call is made lot of time
that will have lot of overhead of calling function creating stack then freeing stack etc..(all the things of function)
now we have inlined function also so are function like macros still useful

#undef
to undefine macro use this
if macro is required to give new value undefine and then use #define again
*/

//TODO: if macro id defined without giving any value what is it replaced with
#define MACRO_IS_DEFINED //define a macro
//TODO: use of #define over const. when ?
#define ANOTHER_MACRO 10 //define macro and give some value

/*
caveats with function like macro:
so these macro's may give surprising result than expected
say for e.g. I define a macro like this
#define MULTI(X) X*X
so i would expect if a pass any no it will multiply by itself and give value back
MULTI(5) => I get expected result as 25
but what if I do this
a variable x defined like this
int x = 2;
MULTI(x+3) => I may expect 25 again but see the answer
MULTI(x+3) converts to x+3*x+3 => 2+3*2+3 => 11 so we get 11
so to avoid this we have to explicit brackets () where expression is expected in macro
TODO: is after inline functions function like macro is dead
*/
#define MAX(X, Y) X > Y ? 1 : 0 //function like macro

#undef ANOTHER_MACRO_DEFINED

/*
#ifdef #ifndef #endif
these are used for checking if some macro is defined using #define or not
#include
this includes all the contents of a file in the file #include is declared
*/

//common way files are included checking a macro
#ifndef MACRO_IS_DEFINED
#define MACRO_IS_DEFINED
#include <string.h>
#endif

//a struct whose one field is optional and appears only when this macro MACRO_IS_DEFINED is defined
struct Human{
    int a;
    int b;
#ifdef MACRO_IS_DEFINED
    char name[100]; //this field is available only when macro is defined
#endif
};

//usual include call
#include <stdlib.h>
#include <stdio.h>

/*
#if #else #elif
these work exactly like if else if and else in c code
*/
int x = 0;
//TODO: can #if use regular variable instead of macro for true/false testing
//FIXME: fix the error here
// #if ANOTHER_MACRO == 20
//     printf("%d",x);
// #elif ANOTHER_MACRO == 10
//     printf("%d",x);
// #else
//     printf("%d",x);
// #endif

/*
#line #error #pragma
*/
#line 10       //set this line no as 10
#pragma c9x on //enable/disable a compiler feature using pragma macro

// #error big_error //throw error using preprocessor

/*
predefined macros:
__DATE__
__FILE__
__LINE__
__STDC__
__STDC_VERSION__
__TIME__
*/

void predefined_macros(){
    printf("%s\t %s\t %lu\t %s", __DATE__, __FILE__, __STDC_VERSION__, __TIME__);
}

int main(){
    predefined_macros();
}
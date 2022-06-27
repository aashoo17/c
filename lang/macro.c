/*
#define
1. define constant
2. define function like macro
TODO: #define vs const
#undef
*/

// TODO: if macro id defined without giving any value what is it replaced with
#define MACRO_IS_DEFINED // define a macro
// TODO: use of #define over const. when ?
#define ANOTHER_MACRO 10 // define macro and give some value

#define MAX(X, Y) X > Y ? 1 : 0 // function like macro

#undef ANOTHER_MACRO_DEFINED

// #ifdef #ifndef #endif

/*
common way files are included checking a macro
#ifndef MACRO_IS_DEFINED
  #define MACRO_IS_DEFINED
  #include <string.h>
#endif
*/

// a struct whose one field is optional and appears only when this macro
// MACRO_IS_DEFINED is defined
struct Human {
  int a;
  int b;
#ifdef MACRO_IS_DEFINED
  char name[100]; // this field is available only when macro is defined
#endif
};

// usual include call
#include <stdio.h>
#include <stdlib.h>

/*
#if #else #elif
these work exactly like if else if and else in c code
*/
int x = 0;
// TODO: can #if use regular variable instead of macro for true/false testing
// FIXME: fix the error here
#if ANOTHER_MACRO == 20
    #define IF_CREATED_MACRO 
#elif ANOTHER_MACRO == 10
    #undef IF_CREATED_MACRO
    #define IF_CREATED_MACRO
#else
    printf("%d",x);
#endif

/*
#line #error #pragma
*/
#line 10       // set this line no as 10
#pragma c9x on // enable/disable a compiler feature using pragma macro

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

void predefined_macros() {
  printf("%s\t %s\t %lu\t %s", __DATE__, __FILE__, __STDC_VERSION__, __TIME__);
}

int main() { predefined_macros(); }
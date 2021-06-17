#include <stdio.h>
#include <string.h>     //string functions

//string functions
void string_functions(){
    //strcpy(), strlen(), strcmp(), strcat()
    char a[] = "Hello World";
    char b[50];

    strcpy(b, a);
    puts(b);
    printf("%ld\n",strlen(b));
    printf("%d\n",strcmp(b, a));
    strcat(b, a);
    puts(b);
}

//mem functions
void mem_functions(){
    //memcpy(), memcmp(), memset(),memmove()
    char a[] = "Hello World from Ashu";
    char b[50];
    memcpy(b, a, strlen(a));
    puts(b);
    printf("%d\n",memcmp(b, a,strlen(a)));
    //get length
    size_t len = strlen(a);
    //this should be used when memory is overlapped by two variables, though works if not overlapped too
    memmove(b, a, len);   
    puts(b);
    memset(b, 81, sizeof(a));
    puts(b);
}

int main(){
    mem_functions();
}


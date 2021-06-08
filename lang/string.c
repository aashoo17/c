#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void srring_basics()
{
    //string - array of characters
    char a[] = "Hello World"; //we can write as {'H','e','l'.......,'\0'} also

    //use string functions to operate on them
    //strcpy
    char b[100];
    strcpy(b, a);
    printf("%s\n", b);

    //strlen
    printf("%ld\n", strlen(a));

    //strcmp
    printf("%d\n", strcmp(b, a));

    //strcat
    strcat(b, a);
    printf("%s\n", b);

    //all possible string types
    //stack based
    char c[] = "Some string";

    //heap based
    char *d = malloc(100);
    //non modifiable - stored in executable binary
    char *e = "Hello there";
}
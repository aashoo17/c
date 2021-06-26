#include <bits/time.h>
#include <stddef.h>
#include <time.h>
#include <stdio.h>

int main(){
    time_t a = time(NULL);
    // printf("%ld\n",a);
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    struct tm* tm1 = gmtime(&a);
    char *b = asctime(tm1);
    puts(b);
}
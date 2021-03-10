#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//integers
//fixed integers types
void fixed_integer_types(){
    //signed types
    int8_t a = 10;
    int16_t b = 10;
    int32_t c = 10;
    int64_t d = 10;

    //unsigned types
    uint8_t e = 10;
    uint16_t f = 10;
    uint32_t g = 10;
    uint64_t h = 10;

    //enough to store pointer size - 32/64 bit based on platform
    uintptr_t i = 10;
}

//floats
void float_types(){
    float a = 10;
    double b = 10;
}

//bools
void bool_types(){
    bool a = true;
    bool b = false;
}

//chars
void char_types(){
    char a = 'A';
    char b = '\0';
}
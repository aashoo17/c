/*
operators => | & ^ << >> and |= &= ^= <<= >>=
*/
void bit_operators(){
    int a = 10;
    int b = 30;

    int c = a | b;
    int d = a & b;
    int e = a ^ b;
    int f = a << 3;
    int g = b >> 2;

    b |= a;
    a = 10;
    b = 30; //just reassign the values back to get results as in previous lines

    b &= a;
    a = 10;
    b = 30;

    b ^= a;
    a = 10;
    b = 30;

    b >>= 2;
    a <<= 3;
}

/*
bit fields:
bit field can be used like enum say we want a value vary from 0 to 10 we need atleast 4 bits
so we can take atleast char type and set to use its 4 bits
*/

typedef struct{
    int age : 4;                           //say possible age is 1 to 10 then we need 4 bits, we may take char in place of int also, apart from 4 bits will be possibly 0
    unsigned char flags : 2;               //say poossible flags need 4 values max
    unsigned char random : 1, random2 : 2; //even we can have 2 or more parts for bit field - char allows 8 bits we are using 3 here
} Ash;

void bit_field(){
    Ash ash;

    ash.age = 0b0110; //isn't is better to set bitfield in binary so we can visually see each bit value set
    ash.flags = 0b10;
    ash.random = 1;
    ash.random2 = 2;
}
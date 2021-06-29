#include <stddef.h>
#include <stdio.h>
#include <unistd.h>     //this also have definition of crypt() - crypt.h can aslo be used
// #include <crypt.h>   //this can also be used for crypt()
#include <sys/random.h>     //for getting random data
#include <string.h>

/*
cryptographic hash:
get sha-2-512,sha-2-256 and md5 hashes
they need to be linked against -lcrypt library also 
using make caveat
```make
all:main
	./main
	rm main
# -lcrypt will link against libcrypt
main:crypto.c -lcrypt
    # use $? as automatic variable
    # if $< is used it will take only 1st prequisite so linking will fail
	gcc -o $@ $?
```

2nd arg of crypt() controls that which algorithm will be used - names as salt

One-way     function    Prefix Random sequence
SHA-2-512   ‘$6$’       16 characters           => e.g. $6$abcdefghijklmnop
SHA-2-256   ‘$5$’       16 characters           => e.g. $5$abcdefghijklmnop
MD5         ‘$1$’       8 characters            => e.g. $1$abcdefgh

TODO: what will happen when we use say $6$ab or even just $6$ i.e. less that 16 chars after $6$
*/


//getting random data in c
void random_buffer(){
    unsigned char buf[16];
    unsigned char buf2[16];
    //TODO: see the use cases of getentropy() vs getrandom()
    getentropy(buf, 16);
    /*
    GRND_RANDOM - Use the /dev/random (blocking) source instead of the /dev/urandom (non-blocking) source to obtain randomness.
    GRND_NONBLOCK - Instead of blocking, return to the caller immediately if no data is available.
    GRND_INSECURE - Write random data that may not be cryptographically secure.
    */
    getrandom(buf2, 16, GRND_RANDOM);

    for (size_t i = 0; i < 16;  i++){
        printf("%d,",buf[i]);
    }
    printf("\n");
    for (size_t i = 0; i < 16;  i++){
        printf("%d,",buf2[i]);
    }
    printf("\n");
}

void crypto_hash(){
    //TODO: use previously generated hash for salt
    //sha-2-512
    char *a = crypt("Hello World","$6$");
    printf("%s\n",a);
    //sha-2-256
    char *b = crypt("Hello World","$5$");
    printf("%s\n",a);
    //md5
    char *c = crypt("Hello World","$1$");
    printf("%s\n\n",a);
    //TODO: error handling - NULL or * based printable ascii is returned , how can we handle the error
    //a,b,c are here static allocation that means they live till program does not exit
    //TODO: so crypt modifies the same static allocation ?? as this print gives same result
    // printf("%s\n%s\n%s\n",a,b,c);    //this will give same result as pointer pointing to same static allocations
}

int main(){
    crypto_hash();
}

//TODO: what about rsa and ed25519 in c
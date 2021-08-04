#include <errno.h>  //gives errno
#include <fcntl.h>  //gives open()
#include <stdio.h>  //gives printf()
#include <string.h> //gives strerror() and perror()

/*
Error:
normally functions in will return some integers, few of them will mark as error
and some success say -1 for error 0 for success etc and errno is a variable
which will be set to a value which will be telling actual error, we can get text
related to error using strerror() and perror()

TODO:
we have some error code - macros basically like EPERM, ENOENT
if we want to throw them - say my function throws 15 of them
how can I handle all of them
do all of these macros +ve no or all are -ve no are any no except 0
so that we can check
if(return_value_from_function is -ve or +ve){
    handle error here
}
*/

// check values of error nos
// TODO: check in what range error values lies - all +ve, all -ve , both ??
void check_err_value() {
  // it seems like it starts from 1 and keeps on increasing in +ve side by 1
  printf("%d %d %d %d %d %d\n", EPERM,ENOENT,ESRCH,EINTR,EIO,ENXIO);
  // if we return the built in error type it will be always +ve then so in a if
  // block we can just check if return value is +ve

  // but there can be other possible ways -> -ve is error, +ve value error etc
  // so there is not much convention so we have to always look for what return
  // value function thinks as error
}

void handle_error() {
  // say file reading error
  int fd = open("file.txt", O_RDWR); // if file.txt is not available in current
                                     // directory - error is thrown
  if (fd == -1) {
    printf("%s\n", strerror(errno));
    // custom error
    perror("custom error");
    perror(""); // passing "" or NULL will work like
                // printf("%s\n",strerror(errno));
  }
}

int main() { handle_error(); }
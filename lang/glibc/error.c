#include <stdio.h>   //gives printf()
#include <errno.h>  //gives errno
#include <string.h> //gives strerror() and perror()
#include <fcntl.h>     //gives open()

/*
Error:
normally functions in will return some integers, few of them will mark as error and some success
say -1 for error 0 for success etc
and errno is a variable which will be set to a value which will be telling actual error, we can get
text related to error using 
strerror() and perror()
*/

int main(){
    //say file reading error
    int fd = open("file.txt", O_RDWR);  //if file.txt is not available in current directory - error is thrown

    if(fd == -1){
        printf("%s\n",strerror(errno));
        //custom error
        perror("custom error");
        perror("");     //passing "" or NULL will work like printf("%s\n",strerror(errno));
    }
}
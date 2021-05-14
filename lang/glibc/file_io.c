#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//high level io portable and buffered
void file_pointer(){
    FILE* f = fopen("file.txt", "w");
    char buf[] = "Hello World from me";
    fwrite(buf, 1, strlen(buf), f);
    fclose(f);
}

//low level fd non portable
void fd_based_io(){
    int fd = open("file.txt",O_WRONLY | O_CREAT);

    char buf[] = "Hello World";
    write(fd, buf, strlen(buf));
    close(fd);
}

int main(){
    fd_based_io();
}
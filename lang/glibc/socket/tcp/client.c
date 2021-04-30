#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main(){
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(3000);
    addr.sin_family = AF_INET;  //address family not supported by protocol error - when this line was not declared

    if(connect(fd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
        perror("");
    };

    char buf[] = "Hello World";
    write(fd,buf,sizeof(buf));
    read(fd,buf,strlen(buf));
    close(fd);
}
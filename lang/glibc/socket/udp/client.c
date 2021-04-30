#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main(){
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;  //ipv4 family
    addr.sin_port = htons(3000);    //port
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);   //ip address - loopback i.e. 127.0.0.1 here

    if(connect(client_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) == -1){
        perror("");
    };

    char buf[100];
    while(1){
        recv(client_fd, buf, sizeof(buf), 0);
        send(client_fd, buf, strlen(buf), 0);
    }
    close(client_fd);
}
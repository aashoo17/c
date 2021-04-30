#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main(){
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    //create address
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;  //ipv4 family
    addr.sin_port = htons(3000);    //port
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);   //ip address - loopback i.e. 127.0.0.1 here

    if(bind(server_fd,(struct sockaddr*)&addr,sizeof(struct sockaddr_in)) == -1)
        perror("");

    char buf[100];
    //start sending and receaving data
    while(1){
        //client address detail filled in this struct
        struct sockaddr_in cl_addr;
        socklen_t len;
        //first wait for any client to send data 
        recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr*)&cl_addr, &len);
        //and in turn send him data back
        //FIXME: I am sending something unexpected when no data is received apart i.e. enter key is hit by client 
        sendto(server_fd, buf, strlen(buf), 0, (struct sockaddr*)&cl_addr, sizeof(struct sockaddr_in));
    }
    close(server_fd);
}
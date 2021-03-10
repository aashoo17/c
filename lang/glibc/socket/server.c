#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

//this function will be made available by addr.c when addr.o is linked with server.o
struct sockaddr* create_internet_address();

//create tcp server
void tcp_server(){
    int fd = socket(PF_INET, SOCK_STREAM, 0);   //create socket
    struct sockaddr* addr = create_internet_address();
    bind(fd, addr, sizeof(struct sockaddr_in));     //bind the address to socket
    listen(fd, 10);     //start listening on this socket

    //TODO: why socklen_t type is used for sizes not size_t
    struct sockaddr client_addr;    //address of client which will be connecting
    socklen_t client_addr_len;      //client address length
    accept(fd, &client_addr, &client_addr_len);     //start accepting connections from clients

    char buf[20];   //allocate a buffer
    read(fd,buf,12);    //read 12 bytes from client (12 bytes as i am writing "Hello World" from client side)
    puts(buf);
}

int main(){
    tcp_server();
}
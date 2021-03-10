#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

struct sockaddr* create_internet_address();

//create tcp client
void tcp_client(){
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr* addr = create_internet_address();
    connect(fd, addr, sizeof(struct sockaddr_in));

    char buf[] = "Hello World";
    write(fd,buf,strlen(buf));
    close(fd);
}

int main(){
    tcp_client();
}
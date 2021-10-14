// server based on epoll api
// create a server which replies to those clients only which are ready for read and write 
// so that server machine's thread is not blocked waiting
#include <sys/epoll.h>
#include <sys/socket.h>
#include <stdio.h>

void epoll(){
    int epfd = epoll_create(100);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("%d\n",fd);
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT;
    ev.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);

    struct epoll_event evlist[1];
    epoll_wait(epfd, &evlist[0], 1, 0);

    printf("%d\n",evlist[0].data.fd);
}

int main(){
    epoll();
}
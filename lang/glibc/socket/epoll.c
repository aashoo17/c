// server based on epoll api
// create a server which replies to those clients only which are ready for read and write 
// so that server machine's thread is not blocked waiting
#include <sys/epoll.h>
#include <sys/socket.h>
#include <stdio.h>

/*
create an empty epoll structure - with nil fd to monitor 
add fd to this epoll structure 
events - these are the things we want to track on a fd like read, write readiness
get the result corresponding to all fd for the corresponding event
if ready for the event use the normal read/write calls which will not block the thread
*/

void epoll(){
    // create a epoll structure internally pointed by a number epfd
    // epoll interest list by default is empty - no fd is there to be checked for any kind of events
    int epfd = epoll_create1(EPOLL_CLOEXEC);

    //TODO: make the fd full fledged server and then monitor here
    // create a socket fd which we will check for its readiness
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("%d\n",fd);  //print to see value

    // create the event we want to track out of a fd
    /*
    EPOLLIN - Data other than high-priority data can be read
    EPOLLPRI - High-priority data can be read
    EPOLLRDHUP - Shutdown on peer socket (since Linux 2.6.17)
    EPOLLOUT - Normal data can be written
    EPOLLET - Employ edge-triggered event notification
    EPOLLONESHOT - Disable monitoring after event notification
    EPOLLERR - An error has occurred
    EPOLLHUP - A hangup has occurred
    */
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT;
    ev.data.fd = fd;    //add the extra data in union as fd
    // add the fd to be checked for its readiness
    /*
    EPOLL_CTL_ADD - add the fd in interest list 
    EPOLL_CTL_MOD - modify the event we want to check on fd
    EPOLL_CTL_DEL - delete the fd from interest list
    */
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);

    struct epoll_event evlist[1];
    // evlist has array of fds which are ready now - here evlist i.e.  epoll_event's events field will tell for which event we are ready
    // and its other field comes whatever is added in epoll_ctl will be intact to know for which fd it is 
    // since we have populated fd field of epoll_event we get back the fd field back
    epoll_wait(epfd, &evlist[0], 1, 0);

    printf("%d\n",evlist[0].data.fd);   //print the fd field and check if same value of fd in socket creation is matching
}

int main(){
    epoll();
}
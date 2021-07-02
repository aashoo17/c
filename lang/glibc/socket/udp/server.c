#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_fd == -1) {
    perror("");
    exit(1);
  }

  // create address
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;   // ipv4 family
  addr.sin_port = htons(3000); // port
  // ip address - loopback i.e. 127.0.0.1 here
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (bind(server_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) ==
      -1) {
    perror("");
    exit(1);
  }

  char buf[100];
  // start sending and receaving data
  // client address detail filled in this struct
  struct sockaddr_in cl_addr;
  socklen_t len;
  while (1) {
    // first wait for any client to send data
    recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr *)&cl_addr, &len);
    // and in turn send him data back
    // fixme: I am sending something unexpected when no data is received apart
    // i.e. enter key is hit by client
    sendto(server_fd, buf, strlen(buf), 0, (struct sockaddr *)&cl_addr,
           sizeof(struct sockaddr_in));
  }
  close(server_fd);
}
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
    exit(server_fd);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;   // ipv4 family
  addr.sin_port = htons(3000); // port
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (bind(server_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) {
    perror("");
    exit(-1);
  }

  char buf[100];
  struct sockaddr_in cl_addr;
  socklen_t len;
  while (1) {
    recvfrom(server_fd, buf, sizeof(buf), 0, (struct sockaddr *)&cl_addr, &len);
    puts(buf);
    sendto(server_fd, buf, strlen(buf), 0, (struct sockaddr *)&cl_addr,sizeof(struct sockaddr_in));
    memset(buf, 0, sizeof(buf));
  }
}
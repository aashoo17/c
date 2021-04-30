#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0); // tell to use tcp explicitly
  if (sock == -1) {
    perror("");
  }

  struct sockaddr_in addr;
  addr.sin_port = htons(3000);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_family = AF_INET;  //address family not supported by protocol error - when this line was not declared

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("");
  };
  if(listen(sock, 128) == -1){
    perror("");
  };

  // client address
  struct sockaddr_in cl_addr;
  socklen_t len;

  // buf to read/write from/to
  char buf[100];

  // all this will be blocking code
  while (1) {
    int fd = accept(sock, (struct sockaddr*)&cl_addr, &len);
    read(fd, buf, sizeof(buf));
    write(fd, buf, strlen(buf));
    close(fd);
  }
}
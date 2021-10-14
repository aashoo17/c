#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  // socket creation 
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("");
    exit(fd);
  }

  // create the address socket will connect to
  struct sockaddr_in addr;
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_port = htons(3000);
  addr.sin_family = AF_INET;

  // make the tcp connection
  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("");
    exit(-1);
  };

  char buf[100];

  // loop and make write and read infinitely
  while (1) {
    read(fd, buf, sizeof(buf));
    write(fd, buf, strlen(buf));
    puts(buf);
  }
}
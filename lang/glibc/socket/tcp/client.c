#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("");
    exit(1);
  }

  struct sockaddr_in addr;
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_port = htons(3000);
  addr.sin_family = AF_INET;

  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("");
    exit(1);
  };

  char buf[] = "Hello World\n";
  char buf2[100];
  while (1) {
    write(fd, buf, strlen(buf));
    //fixme: first time when buffer is read it gives all the data back to server even the garbage value
    read(fd, buf2, strlen(buf));
    puts(buf2);
    memset(buf2, 0, sizeof(buf2));
  }
}
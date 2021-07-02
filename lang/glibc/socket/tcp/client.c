#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // with 0 default protocol is selected
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("");
    exit(1);
  }

  struct sockaddr_in addr;
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_port = htons(3000);
  // address family not supported by protocol error - when this line was not
  // declared
  addr.sin_family = AF_INET;

  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("");
    exit(1);
  };

  char buf[] = "Hello World\n";
  char buf2[50];
  while (1) {
    write(fd, buf, sizeof(buf));
    //todo: if next read buffer is smaller in size it emits previos data also
    read(fd, buf2, strlen(buf));
    puts(buf2);
  }
  close(fd);
}
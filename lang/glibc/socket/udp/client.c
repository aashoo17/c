#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1) {
    perror("");
    exit(fd);
  }

  struct sockaddr_in addr;
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_port = htons(3000);
  addr.sin_family = AF_INET;

  if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("");
    exit(-1);
  };

  char buf[] = "Hello World\n";
  char buf2[50];
  //fixme: when no server is runing on the address this code keep on looping indefinitely
  while (1) {
    //making buffer is zero is good in sense when new data is written after that existing 0 will feel like null to all text programs
    memset(buf2, 0, sizeof(buf2));
    write(fd, buf, strlen(buf));
    read(fd, buf2, strlen(buf));
    puts(buf2);    
  }
}
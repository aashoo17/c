#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (client_fd == -1) {
    perror("");
    exit(1);
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;   // ipv4 family
  addr.sin_port = htons(3000); // port
  // ip address - loopback i.e. 127.0.0.1 here
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  //connect usually not required in udp client - as client are not connected like tcp
  //it is just use to know where we are sending/receiving data from 
  //this in turn can use simple read()/write() call which will not require address
  //as connect() has already tells that
  if (connect(client_fd, (struct sockaddr *)&addr,
              sizeof(struct sockaddr_in)) == -1) {
    perror("");
    exit(1);
  };

  char buf[100];
  //fixme: client is not working
  while (1) {
    read(client_fd, buf, sizeof(buf));
    puts(buf);
    write(client_fd, buf, strlen(buf));
    memset(buf, 0, sizeof(buf));
  }
  close(client_fd); //not required
}
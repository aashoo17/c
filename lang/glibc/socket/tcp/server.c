#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // todo: tell to use tcp explicitly
  /*
  AF_INET - ipv4 uses
  AF_INET6 - ipv6 uses
  AF_UNIX - process on same computer

  SOCK_STREAM - stream socket
  SOCK_DGRAM - datagram socket
  */
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("");
    exit(1);
  }
  //todo: how pointer to struct sockaddr_in and sockaddr can be converted from one to another
  struct sockaddr_in addr;
  addr.sin_port = htons(3000);
  // todo: conversion functions from human readable 127.0.0.1 to binary big
  // endian form
  //INADDR_LOOPBACK is const defined for - 127.0.0.1
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  // address family not supported by protocol error - when this line was not
  // declared
  addr.sin_family = AF_INET;

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("");
    exit(1);
  };
  //backlog connections - 128
  if (listen(sock, 128) == -1) {
    perror("");
    exit(1);
  };

  // client address
  struct sockaddr_in cl_addr;
  socklen_t len;

  // buf to read/write from/to
  char buf[100];

  // all this will be blocking code
  while (1) {
    int fd = accept(sock, (struct sockaddr *)&cl_addr, &len);
    read(fd, buf, sizeof(buf));
    write(fd, buf, strlen(buf));
    //fixme: client is not closing connection after close() call
    close(fd);
  }
}
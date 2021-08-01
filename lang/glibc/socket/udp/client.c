#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/*
networking:
socket are a way for inter process communication mechanism
this is special in a way that you can share data between process on same
computer as well as on network (connected via wire/wireless)
two major type of sockets are used
1. stream socket - data can be read/written in any size - tcp protocol is most
popular for stream socket operations
2. datagram socket - data can be read/written in fixed sizes called as datagram
- udp protocol is most popular for datagram socket operations
*/
int main() {
  // AF_INET - tells to use ipv4, SOCK_STREAM - tells to create stream socket, 0
  // - use default protocal which is tcp
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1) {
    perror("");
    exit(1);
  }
  // todo: conversion functions from 127.0.0.1 to bytes form
  /*
  address:
  connecting to processes was abstracted with the idea of address struct
  since socket can talk to process on same machine and even on processes on
  network we needed to have different address struct for different domains
  network over ipv4 uses - struct sockaddr_in,
  todo: ipv6 and local computer address struct ??
  so a generic struct was created struct sockaddr and all domain specific
  structs are casted into it using generic struct gives a common api for all the
  domains rather than using different function/api
  */
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
    // write the buffer on the server socket
    write(fd, buf, strlen(buf));
    // read the data from server in a buffer
    //fixme: first time when buffer is read it gives all the data back to server even the garbage value
    read(fd, buf2, strlen(buf));
    // print the data read from the server
    puts(buf2);
    //clear the buffer - so that in next iteration previous data will not be printed
    memset(buf2, 0, sizeof(buf2));
  }
  close(fd);
}
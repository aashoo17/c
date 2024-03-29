#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("");
    exit(sock);
  }
  struct sockaddr_in addr;
  addr.sin_port = htons(3000);
  // todo: conversion functions from human readable 127.0.0.1 to binary big endian form
  // todo: if INADDR_LOOPBACK is const defined for - 127.0.0.1, what is INADDR_ANY then
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_family = AF_INET;

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("");
    exit(-1);
  };
  // backlog connections => 128
  if (listen(sock, 128) == -1) {
    perror("");
    exit(-1);
  };

  // client address
  struct sockaddr_in cl_addr;
  socklen_t len;

  // buf to read/write from/to
  char buf[100];

  // all this will be blocking code
  // todo: all the time i am talking to the same client how can we talk to many
  // of them in single threaded environment without creating new process or
  // thread
  //todo: is accept not required to put in loop to accept connection from other clients
  // backlog input does point to this theory
  //current server accepts the connection from more than 1 client without keeping accept in  loop
  // TODO: if in accept() call we keep backlog as 1 then do we have to put accept() in the loop
  int fd = accept(sock, (struct sockaddr *)&cl_addr, &len);
  //this will block the thread and it will accept the connection from other client but will not respond
  //since server will be busy with single client as read/write calls keep on happening in loop
  while (1) {
    read(fd, buf, sizeof(buf));
    puts(buf);
    write(fd, buf, strlen(buf));
    memset(buf,0,sizeof(buf));
  }
}
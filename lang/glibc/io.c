#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// high level io portable and buffered
void file_pointer() {
  FILE *f = fopen("file.txt", "w");
  // TODO: error handling
  char buf[] = "Hello World from me";
  fwrite(buf, 1, strlen(buf), f);
  fclose(f);
}

// low level fd non portable
void fd_based_io() {
  int fd = open("file.txt", O_WRONLY | O_CREAT);
  // TODO: error handling
  char buf[] = "Hello World";
  write(fd, buf, strlen(buf));
  close(fd);
}

int main() { fd_based_io(); }
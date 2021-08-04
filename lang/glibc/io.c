#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// high level io portable and buffered
void file_pointer() {
  /*
  r = reading only
  w = writing only, if file available truncate to zero else create one
  a = write but append does not truncate
  r+ = reading and writing, no truncation but file pointer to beginning of file
  w+ = reading and writing, if file available truncate to zero else create one
  a+ = reading and appending, if file exist initial content unchanged else new
  created, initial position for reading at beginning of file but content is
  appended at the end
  */
  FILE *f = fopen("file.txt", "w+");
  if (f != NULL) {
    char buf[] = "File pointer";
    fwrite(buf, 1, strlen(buf), f);
    // TODO: if NULL received do we need to close the file - I don't think so
    fclose(f);
  }else{
    perror("");
  }
}

// low level fd non portable
void fd_based_io() {
  /*
  O_RDONLY - read only access
  O_WRONLY - write only access
  O_RDWR - read and write access
  O_CREAT - create if not available
  O_TRUNC - truncate to zero 
  */
  int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC);
  if (fd != -1) {
    char buf[] = "from fd";
    write(fd, buf, strlen(buf));
    close(fd);
  } else {
    perror("");
  }
}

int main() { file_pointer(); }
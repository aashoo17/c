#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>   //fork()
#include <sys/wait.h>

// signal handler function
void handler(int signum) { printf("got signal ctrl + c as = %d\n", signum); }

// todo: create a child process and pid will be known issue signal using kill()
int main() {
  pid_t pid = fork();
  if (pid == 0) {
    // handle ctrl + c
    //fixme: handler is not getting called 
    signal(SIGINT, handler);
    // Wait for a signal to be received
    printf("Hello World!\n");
    pause();
    // send SIGINT from command line by pressing ctrl + c
  }
  kill(pid, SIGINT);
  int status;
  waitpid(pid, &status, WAIT_ANY);
  
}

// generating signal
void generate_signal() {
  // generate to yourself
  // this is used for testing usually
  raise(SIGINT);
  // signal to other process
  pid_t pid = fork();
  kill(pid, SIGINT);

  // kill thread
  pid_t tid = 2; // random thread id i have given
  // todo: get its header file
  // tgkill(pid,tid,SIGINT);
}
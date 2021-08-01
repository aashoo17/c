#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

/*
process:
fork() will create a new process
fork() returns in child pid in parent process and 0 in child process
fork() may fail so error handling should be given
after fork() call both parent and child process have loaded the same program so
they will start same command/lines in code after fork - same binary code is
loaded for child process also generally exec() family is called to load the
child process with different program to execute
*/

// process creation
void process_create() {
  pid_t pid = fork();
  // this line will be printed 2 times as both parent and child process will
  // execute it
  puts("Hello World");
}

/*
execv(), execl(), execve(), execle(), execvp(), execlp()
load different program in child process for execution by exec() family
*/
void exec_family() {
  // trying to spawn child processes and ensure execution of all
  // TODO: show env uses by passing some values
  pid_t p1 = fork();
  if (p1 == -1) {
    perror("");
  } else {
    if (p1 == 0) {
      char *arg[] = {"la", NULL}; // args to command
      execv("/bin/ls", arg);       // full file path is required
    }
    pid_t p2 = fork();
    if (p2 == 0) {
      execl("/bin/ls", "-la", NULL); // full file path + arg as variadic char*
    }
    pid_t p3 = fork();
    if (p3 == 0) {
      char *arg[] = {"-la", NULL}; // args to command
      char *env[] = {"CC=gcc",NULL};
      execve("/bin/ls", arg,
             NULL); // full file path + arg as char** + env as char*
    }
    pid_t p4 = fork();
    if (p4 == 0) {
      char *arg[] = {"-la", NULL}; // args to command
      char *env[] = {}; // explicit custom environment variable passing
      execle("/bin/ls", "-la", NULL, env);
    }
    pid_t p5 = fork();
    if (p5 == 0) {
      char *arg[] = {"-la", NULL}; // args to command
      execvp("ls", arg); // path is also searched using $PATH environment variable
    }
    pid_t p6 = fork();
    if (p6 == 0) {
      execlp("ls", "-la", NULL);
    }
  }
}

// wait for child process completion
void wait_for_child_process() {
  pid_t pid = fork();
  // let child process run ls command
  if (pid == 0) {
    char *arg[] = {"-la", NULL};
    execvp("ls", arg);
  }
  int status_ptr;
  /*
  WAIT_ANY - waitpid should return status information about any child process
  WAIT_MYPGRP - waitpid should return status in-formation about any child
  process in the same process group as the calling process. WNOHANG - waitpid
  should return immediately instead of waiting, if there is no child process
  ready to be noticed WUNTRACED - report the status of any child processes that
  have been stopped as well as those that have terminated
  */
  waitpid(pid, &status_ptr, WUNTRACED);
  // wait(&status_ptr);  //this is simplified version of the call waitpid()
  // wait4(pid, &status_ptr, WUNTRACED, NULL);     //this call is also similar
  // to waitpid()
  printf("%d\n", status_ptr);
}

int main() { exec_family(); }

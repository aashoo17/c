#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
process:
fork() will create a new process
fork() returns in child pid in parent process and 0 in child process
fork() may fail so error handling should be given
after fork() call both parent and child process have loaded the same program so they will start same command/lines in code after fork
generally exec() family is called to load the child process with different program to execute
*/

//process creation
void process_create(){
    pid_t pid = fork();
    //this line will be printed 2 times as both parent and child process will execute it
    puts("Hello World");
}

//load different program for execution by exec() family
void exec_use(){
    pid_t pid = fork();
    //let child process run ls command
    if(pid == 0){
        char *arg[] = {"-la",NULL};
        execvp("ls",arg);
    }
    puts("Hello World");
}

//wait for child process completion
void wait_for_child_process(){
    pid_t pid = fork();
    //let child process run ls command
    if(pid == 0){
        char *arg[] = {"-la",NULL};
        execvp("ls",arg);
    }
    int status_ptr;
    waitpid(pid, &status_ptr, WUNTRACED);
    //wait(&status_ptr);  //this is simplified version of the call waitpid()
    //wait4(pid, &status_ptr, WUNTRACED, NULL);     //this call is also similar to waitpid()    
    printf("%d\n",status_ptr);
}


int main(){
    wait_for_child_process();
}


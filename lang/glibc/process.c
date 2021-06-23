#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
process:
fork() will create a new process
fork() returns in child pid in parent process and 0 in child process
fork() may fail so error handling should be given
after fork() call both parent and child process have loaded the same program so they will start
same command/lines in code after fork - same binary code is loaded for child process also
generally exec() family is called to load the child process with different program to execute
*/

//process creation
void process_create(){
    pid_t pid = fork();
    //this line will be printed 2 times as both parent and child process will execute it
    puts("Hello World");
}

/*
execv(), execl(), execve(), execle(), execvp(), execlp()
*/
void exec_family(){
    char *arg[] = {"-la",NULL};     //args to command
    char *env[] = {};   //explicit custom environment variable passing
    //FIXME: so once exec family is called binary executable itself is changed it will not go to next line after that
    //try to spawn child processes and ensure execution of all
    execv("/bin/ls", arg);  //full file path is required
    execl("/bin/ls", "-la",NULL);   //full file path + arg as variadic char*
    execve("/bin/ls", arg, NULL);   //full file path + arg as char** + env as char*
    execle("/bin/ls", "-la",NULL,env);
    execvp("ls", arg);          //path is also searched using $PATH variable in shell
    execlp("ls", "-la",NULL);
}

//load different program in child process for execution by exec() family
void exec_use(){
    pid_t pid = fork();
    //let child process run ls command
    if(pid == 0){
        char *arg[] = {"-la",NULL};     //NULL terminated array
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
    /*
    WAIT_ANY - waitpid should return status information about any child process
    WAIT_MYPGRP - waitpid should return status in-formation about any child process in the same process group as the calling process.
    WNOHANG - waitpid should return immediately instead of waiting, if there is no child process ready to be noticed
    WUNTRACED - report the status of any child processes that have been stopped as well as those that have terminated
    */
    waitpid(pid, &status_ptr, WUNTRACED);
    //wait(&status_ptr);  //this is simplified version of the call waitpid()
    //wait4(pid, &status_ptr, WUNTRACED, NULL);     //this call is also similar to waitpid()    
    printf("%d\n",status_ptr);
}


int main(){
    exec_family();
}


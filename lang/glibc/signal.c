#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//signal handler function
void handler(int signum){
    printf("got signal ctrl + c as = %d",signum);
}

int main(){
    //handle ctrl + c
    signal(SIGINT, handler);
    //Wait for a signal to be received
    pause();
}

//generating signal
void generate_signal(){
    //generate to yourself
    //this is used for testing usually
    raise(SIGINT);
    //signal to other process
    pid_t pid = fork();
    kill(pid, SIGINT);

    //kill thread
    pid_t tid = 2;  //random thread id i have given
    //TODO: get its header file
    // tgkill(pid,tid,SIGINT);
}
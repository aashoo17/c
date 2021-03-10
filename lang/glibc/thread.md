## Thread
posix thread api vs c11 thread api => pthread.h vs thread.h  


## Mutex
mutex working  

this is the working signature of mutex  
say in a function  
mutex lock
piece of code accessing shared (global = static,extern and heap variables) variables for modifications
mutex unlock

if a thread executes this function and reaches to mutex lock it will not allow the lock to be taken by any other thread until unlocked so other thread will come to lock and will wait untill unlock is called by the previous thread  
so mutex give exclusive access for a piece of code/data to be executed by only one thread at a time. 


mutex is a structure which needs to be initialized with default values to start taking locks  
static/global initialization  
dynamic initialization of mutex  
```c
#include <pthread.h>

int main(){
    //initilize a static mutex
    //TODO: how does a macro initializes the struct since it does not seem to be a functional macro which returns a mutex. is it a variable with default value of struct
    pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;
     
}
```
dynamically created mutex initialization and destroying this mutex
```c
#include <pthread.h>

int main(){
    pthread_mutex_t mux;
    //initializing dynamically allocated mutex
    pthread_mutex_init(&mux,NULL);
    //destroying mutex
    pthread_mutex_destroy(&mux);
}
```
#include <stdio.h>
#include <threads.h>    //ISO-C std threads

//thrd_start_t => int (*) (void *) this function pointer is passed to thread for execution
int run_func(void* x){
    puts("Hello World from thread");
    return 0;
}

//using mutex
int run_func2(){
    mtx_t mux;
    mtx_init(&mux, mtx_plain);
    mtx_lock(&mux);
    //critical section of code - which two thread should not access together
    puts("Hello critical section");
    
    mtx_unlock(&mux);
    mtx_destroy(&mux);
    return 0;
}

//create thread and wait for it to finish
void thread_create(){
    //thread create
    thrd_t thr;
    thrd_create(&thr, run_func, NULL);
    //join the thread i.e. wait for its completion
    int res;
    thrd_join(thr, &res);

    //TODO: call thrd_sleep() to wait for few seconds so that created thread can be executed before main thread exits
}

//thread using mutex
void thread_using_mutex(){
    //thread create
    thrd_t thr;
    thrd_create(&thr, run_func2, NULL);
    //join the thread i.e. wait for its completion
    int res;
    thrd_join(thr, &res);

    //TODO: call thrd_sleep() to wait for few seconds so that created thread can be executed before main thread exits
}

int main(){
    thread_create();
}
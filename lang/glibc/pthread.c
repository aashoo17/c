#include <pthread.h>
#include <stdio.h>

void* run(void* x){
	puts("Hello pthread");
	return NULL;
}

void* run2(void* x){
	pthread_mutex_t t1;
	pthread_mutex_init(&t1, NULL);
	pthread_mutex_lock(&t1);

	//crtical section
	puts("Hello Pthread");

	pthread_mutex_unlock(&t1);
	pthread_mutex_destroy(&t1);
	return NULL;
}

void thread(){
	pthread_t t1;
	pthread_create(&t1, NULL, run, NULL);
	pthread_join(t1, NULL);
}

void thread_using_mutex(){
	pthread_t t1;
	pthread_create(&t1, NULL, run2, NULL);
	pthread_join(t1, NULL);
}

int main(){
	thread();
}
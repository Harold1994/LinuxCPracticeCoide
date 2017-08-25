/*************************************************************************
    > File Name: thread_cancle.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月25日 星期五 20时14分40秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void * thread_function(void* arg);

int main(){
    int res;
    pthread_t a_thread;
    void * thread_result;

    res = pthread_create(&a_thread,NULL,thread_function,NULL);
    if(res != 0){
        perror("Thread creation failed\n");
        exit(EXIT_FAILURE);
    }
    sleep(3);
    printf("Cancleing thread\n");
    res = pthread_cancel(a_thread);

    if(res !=0){
        
        perror("Thread canclation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Waiting thread to finish\n");

    res = pthread_join(a_thread,&thread_result);

    if(res !=0)   {
        perror("Thread join failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg){
    int i,res;
    res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    if(res != 0) {
        perror("Thread setcancelstate failed\n");
        exit(EXIT_FAILURE);
    }
    res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
    if(res != 0) {
        perror("Thread SETCANCELTYPE failed\n");
        exit(EXIT_FAILURE);
    }
    printf("thread function is running");
    for(i = 0; i< 10; i++){
        printf("Thread is still running (%d)",i);
        sleep(1);
    }
    pthread_exit(0);
    
}


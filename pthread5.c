/*************************************************************************
    > File Name: pthread5.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月25日 星期五 18时28分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *thread_function(void *args);

char message[] = "Hello World";
int thread_finished = 0;

int main(){
    int res;
    pthread_t a_thread;

    pthread_attr_t thread_attr;

    res = pthread_attr_init(&thread_attr);
    if(res != 0){
        perror("thread attribute creation failed!\n");
        exit(-1);
    }

    res = pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
    if(res != 0){
        perror("Setting detached attribute failed\n");
        exit(-1);
    }
    res = pthread_create(&a_thread,&thread_attr,thread_function,(void *)message);
    
    if(res != 0){
        perror("thread create failed\n");
        exit(-1);
    }
    (void)pthread_attr_destroy(&thread_attr);
    while(!thread_finished){
        printf("wating for thread to finish\n");
        sleep(1);
    }
    printf("Other thread finished!");
    exit(EXIT_SUCCESS);
}
void *thread_function(void * arg){
    printf("other thread begin to running\n");
    sleep(5);
    printf("Second thread is going to exit\n");
    thread_finished = 1;
    pthread_exit(NULL);
}

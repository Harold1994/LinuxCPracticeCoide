/*************************************************************************
    > File Name: thread3.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月24日 星期四 17时47分27秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void *thread_function(void *arg);
sem_t bin_sem;
#define WORK_SIZE 1024

char work_space[WORK_SIZE];

int main(){
    pthread_t a_thread;
    int res;
    void *thread_result;

    res = sem_init(&bin_sem,0,0);
    if(res != 0){
        perror("Samaphore initialization failed\n");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread,NULL,thread_function,NULL);
    if(res != 0){
        perror("Thread create failed\n");
        exit(EXIT_FAILURE);
    }
    
    printf("input some text emd with \"end\" to finish");
    while(strncmp(work_space,"end",3) != 0){
        fgets(work_space,WORK_SIZE,stdin);
        sem_post(&bin_sem);
    }

    printf("\nWaiting thread to finish...\n");
    res = pthread_join(a_thread,thread_result);

    if(res != 0){
        perror("Thread join failed!\n");
        exit(EXIT_FAILURE);
    }

    printf("Thread joined\n");
    sem_destroy(&bin_sem);

    exit(EXIT_SUCCESS);
}

void * thread_function(void *arg){
    sem_wait(&bin_sem);
    while(strncmp("end",work_space,3) != 0){
        printf("you input %d charactors\n",(int) (strlen(work_space)-1));
        sem_wait(&bin_sem);
    }
    pthread_exit(NULL);
}

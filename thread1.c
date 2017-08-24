/*************************************************************************
    > File Name: thread1.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月24日 星期四 16时07分10秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

char message[] = "hello world";
void *thread_function(void *arg);

int main(){
    pthread_t a_thread;
    int res;
    void *thread_result;

    res = pthread_create(&a_thread,NULL,thread_function,(void *)message);
    if(res != 0){
        perror("Thread created failed!\n");
        exit(EXIT_FAILURE);
    }
    printf("Waiting thread to finish ...\n");
    res = pthread_join(a_thread,&thread_result);
    if(res != 0){
        perror("Thread joined failed\n");
        exit(EXIT_FAILURE);
    }

    printf("thread joined,returned %s\n",(char *)thread_result);
    printf("message now is %s\n",message);
    exit(0);
}

void *thread_function(void *arg){
    printf("Thread_function is running,argument is %s\n",(char *)arg);
    sleep(3);
    strcpy(message,"Bye!");
    pthread_exit("Thank you for the cpu time");
}

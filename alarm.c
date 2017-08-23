/*************************************************************************
    > File Name: alarm.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月23日 星期三 18时25分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>

static int alarm_fired = 0;

void ding(int sig){
    alarm_fired = 1;
}

int main(){
    pid_t pid;

    printf("alarm application starting\n");

    (void)signal(SIGALRM,ding);
    pid = fork();
    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            sleep(5);
            kill(getppid(),SIGALRM);
            exit(0);
    }
    printf("waiting for alarm to fo off\n");
    pause();
    if(alarm_fired){
        printf("Ding\n");
    }
    printf("Done\n");
    exit(0);
}

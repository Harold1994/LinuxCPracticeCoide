/*************************************************************************
    > File Name: ctrlc2.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月23日 星期三 20时42分34秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void ouch(int sig){
    printf("OUCH! - I got signal %d\n",sig);
}
int main(){
    struct sigaction act;

    act.sa_flags = 0;
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);

    sigaction(SIGINT,&act,0);

    while(1){
        printf("Hello world\n");
        sleep(1);
    }
}

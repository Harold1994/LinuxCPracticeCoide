/*************************************************************************
    > File Name: wait.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月23日 星期三 11时18分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    pid_t pid;
    char *message;
    int n;
    int exit_code;
    printf("begin to fork\n");
    pid = fork();

    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "this is a child";
            n=5;
            exit_code=37;           
            break;
        default:
            message="this is parent";
            n = 3;
            exit_code=0;
            break;
    }
    for(;n>0;n--){

        puts(message);
        sleep(1);
    }

    if(pid != 0){
        int stat_val;
        pid_t childpid;
        childpid = wait(&stat_val);

        printf("Child has finishedL PID = %d\n",childpid);
        if(WIFEXITED(stat_val)){
            printf("Child exited with code: %d\n",WEXITSTATUS(stat_val));
        }else{
            printf("chils exits abnormally");
        }
    }
    exit(exit_code);
}





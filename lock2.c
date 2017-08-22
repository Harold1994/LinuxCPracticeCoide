/*************************************************************************
    > File Name: lock2.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月22日 星期二 18时40分48秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
const char *lock_file = "./LCK.test2";
int main(){
    int file_desc;
    int tries = 10;
    while(tries--){
        file_desc = open(lock_file,O_RDWR|O_CREAT|O_EXCL,0444);
        if(file_desc == -1){
            printf("%d - Lock already exist\n",getpid());
            sleep(3);
        }
        else{
            printf("%d -I have exclusive access\n",getpid());
            sleep(1);
            (void)close(file_desc);
            (void)unlink(lock_file);

            sleep(2);
        }
    }
    exit(EXIT_SUCCESS);
}


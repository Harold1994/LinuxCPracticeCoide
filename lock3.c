/*************************************************************************
    > File Name: lock3.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月22日 星期二 20时05分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

const char *test_file = "./test_lock";

int main(){
    int file_desc;
    int byte_count;
    char *byte_to_write = "A";
    struct flock region_1;
    struct flock region_2;
    int res;
    //open a filr
    file_desc = open(test_file,O_RDWR|O_CREAT,0666);
    if(file_desc == -1){
        fprintf(stderr,"can't open %s for read and write",test_file);
        exit(EXIT_FAILURE);
    }

    for(byte_count = 0;byte_count<100;byte_count++){
        (void)write(file_desc,byte_to_write,1);
    }

    //10-30上共享锁（读锁）
    region_1.l_type=F_RDLCK;
    region_1.l_whence=SEEK_SET;
    region_1.l_start=10;
    region_1.l_len=20;
    //40-50上独占锁（写锁）
    region_2.l_type=F_WRLCK;
    region_2.l_whence=SEEK_SET;
    region_2.l_start=40;
    region_2.l_len=10;

    printf("Process %d locking file\n",getpid());
    res = fcntl(file_desc,F_SETLK,&region_1);
    if(res == -1)
        fprintf(stderr,"Failed to lock region_1");
    res = fcntl(file_desc,F_SETLK,&region_2);
    if(res == -1)
        fprintf(stderr,"Failed to lock region_1");
    
    sleep(60);
    printf("Process %d cloding file",getpid());
    close(file_desc);
    exit(EXIT_SUCCESS);
}

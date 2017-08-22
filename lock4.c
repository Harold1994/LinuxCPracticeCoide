/*************************************************************************
    > File Name: lock4.c
    > Author: lihe
    > Mail: 1093362865@qq.com 
    > Created Time: 2017年08月22日 星期二 20时48分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

const char *test_file = "./test_lock";
#define SIZE_TO_TRY 5

void show_lock_info(struct flock *to_show);
int main(){
    int file_desc;
    int res;
    struct flock region_to_test;
    int start_byte;

    file_desc = open(test_file,O_RDWR|O_CREAT,0666);
    if(file_desc == -1){
    fprintf(stderr,"un able to open %s to read and write",test_file);
    exit(EXIT_FAILURE);
    }

    for(start_byte = 0;start_byte<99;start_byte += SIZE_TO_TRY){
        region_to_test.l_type=F_WRLCK;
        region_to_test.l_whence =SEEK_SET;
        region_to_test.l_start=start_byte;
        region_to_test.l_len=SIZE_TO_TRY;
        region_to_test.l_pid=-1;

        printf("Test F_WRLCK on region from %d to %d\n",start_byte,start_byte+SIZE_TO_TRY);

        res = fcntl(file_desc,F_GETLK,&region_to_test);
        if(res == -1){
            fprintf(stderr,"F_GETLK failed");
            exit(EXIT_FAILURE);
        }
        if(region_to_test.l_pid != -1){
            printf("Lock would failed,F_GETLK returned:\n");
            show_lock_info(&region_to_test);
        }else{
            printf("Lock would succeed\n");
        }

        region_to_test.l_type=F_RDLCK;
        region_to_test.l_whence =SEEK_SET;
        region_to_test.l_start=start_byte;
        region_to_test.l_len=SIZE_TO_TRY;
        region_to_test.l_pid=-1;

        printf("Test F_RDLCK on region from %d to %d\n",start_byte,start_byte+SIZE_TO_TRY);

        res = fcntl(file_desc,F_GETLK,&region_to_test);
        if(res == -1){
            fprintf(stderr,"F_GETLK failed");
            exit(EXIT_FAILURE);
        }
        if(region_to_test.l_pid != -1){
            printf("Lock would failed,F_GETLK returned:\n");
            show_lock_info(&region_to_test);
        }else{
            printf("Lock would succeed\n");
        }
    }
    close(file_desc);
    exit(EXIT_SUCCESS);
}
void show_lock_info(struct flock *to_show){

    printf("\tl_type %d, ",to_show->l_type);
    printf("l_whence %d, ",to_show->l_whence);
    printf("l_start  %d, ",(int)to_show->l_start);
    printf("l_len %d, ",(int)to_show->l_len);
    printf("l_pid %d\n",to_show->l_pid);
}


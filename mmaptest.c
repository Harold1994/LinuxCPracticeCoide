#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>

typedef struct {
    int integer;
    char string[24];
} RECORD;

#define NRECORD (100)

int main(){
    RECORD record,*mapped;
    int i,f;
    FILE *fp;
    fp =fopen("records.txt","w+");
    for(i=0; i<NRECORD; i++)
    {
        record.integer = i;
        sprintf(record.string,"RECORD-%d",i);
        fwrite(&record,sizeof(record),1,fp);
    }
    fclose(fp);

    //更改第43条编号为143,并写入字符串
    fp = fopen("records.txt","r+");
    fseek(fp,43*sizeof(record),SEEK_SET);
    fread(&record,sizeof(record),1,fp);

    record.integer = 143;
    sprintf(record.string,"RECORD-%d",record.integer);

    fseek(fp,43*sizeof(record),SEEK_SET);
    fwrite(&record,sizeof(record),1,fp);
    fclose(fp);

    //将记录映射到内存中，更改第43条为243
    f = open("records.txt",O_RDWR);
    mapped = (RECORD *)mmap(0,NRECORD*sizeof(record),PROT_READ|PROT_WRITE,MAP_SHARED,f,0);

    mapped[43].integer=243;
    sprintf(mapped[43].string,"RECORD-%d",243);
    //写回文件
    msync((void *)mapped,NRECORD*sizeof(record),MS_ASYNC);
    //释放内存
    munmap((void *)mapped,NRECORD*sizeof(record));
    close(f);

    exit(0);
}


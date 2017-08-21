#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>

void printdir(char *dir, int depth){
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp=opendir(dir)) == NULL){
        fprintf(stderr,"can not read: %s \n",dir);
        return; 
        }
    chdir(dir);


entry = readdir(dp);
printf("------------------\n%s\n----------------",entry->d_name);
//   while((entry = readdir(dp)) != NULL){
//        lstat(entry->d_name,&statbuf);
//        if(S_ISDIR(statbuf.st_mode)){
//            if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
//                continue;
//            printf("%*s%s/\n",depth,"",entry->d_name);
//            printdir(entry->d_name,depth+4);
//
//            }
//            else
//                printf("%*s%s\n",depth,"",entry->d_name);
//    }
    chdir("..");
    closedir(dp);

}
int main(){
    printf("Scan Directory of /home\n");
    printdir("/home",0);
    printf("done.\n");
    exit(0);
}

#include<stdio.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include <sys/mman.h>


struct student
{
    int id;
    char *name;
    char sex;
}STU;
void sys(char*str)
{
    perror(str);
    exit(-1);
}

int main(int argc,char **argv)
{
    int fd;

    struct student s1;
    struct student *m;

    if(argc<2)
    {
        printf("./a.out file_shared\n");
        exit(-1);
    }
    
    fd=open(argv[1],O_RDONLY);
    if(fd<0)
    {
        sys("open error");
    }
    m=(struct student *)mmap(NULL,sizeof(s1),PROT_READ,MAP_SHARED,fd,0);
    if(m==MAP_FAILED)
    {
        sys("mmap error");
    }
    close(fd);
    while(1)
    {
        printf("id=%d\tname=%s\t%c\t",m->id,m->name,m->sex);
        sleep(2);
    }
    munmap(m,sizeof(s1));

    return 0;
}

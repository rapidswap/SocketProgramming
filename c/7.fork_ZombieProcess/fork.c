#include<stdio.h>
#include<unistd.h>

int gval=10;
int main(int argc,char*argv[])
{
    pid_t pid;
    int lval=20;
    gval++, lval+=5;
    
    pid=fork();
    if(pid==0)//if child process
        gval+=2,lval+=2;
    else
        gval-=2, lval-=2;

    if(pid==0)
        printf("Child Proc= [%d, %d] \n",gval, lval); //자식 프로세스는 각 2씩 더해준~
    else
        printf("parent Proc= [%d, %d] \n",gval, lval);//부모는 2씩 빼준!
    return 0;
}
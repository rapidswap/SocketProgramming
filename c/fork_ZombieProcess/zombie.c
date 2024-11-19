#include<stdio.h>
#include<unistd.h>

int main(int argc,char*argv[])
{
    pid_t pid=fork();

    if(pid==0)
    {
        puts("Hi, I am a child process");
    }
    else
    {
        printf("Child Process ID: %d \n",pid);
        sleep(30); //좀비프로세스 때문에 부모 프로세스의 종료를 지연시켜야됨.
        // 그래서 해결을 어떻게 하냐 그것은 wait 함수를 사용해야됨
    }
    if(pid==0)
        puts("End child process");
    else
        puts("End parent process");
    return 0;
}
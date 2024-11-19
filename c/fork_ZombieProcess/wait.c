#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h> //wait 함수 쓰기위해

int main(int argc,char *argv[])
{
    int status;
    pid_t pid=fork();

    if(pid==0)
    {
        return 3; //자식 프로세스가 종료되면 종료 신호를 줘야함 이번엔 3
    }
    else
    {
        printf("Child PID: %d \n",pid);
        pid=fork();
        if(pid==0)
        {
            exit(7);
        }
        else
        {
            printf("Child PID: %d\n",pid);
            wait(&status);
            if(WIFEXITED(status))
                printf("Child send one: %d\n",WEXITSTATUS(status));

            wait(&status);
            if(WIFEXITED(status))
                printf("Child send two: %d\n",WEXITSTATUS(status));
            sleep(30);
        }
    }
    return 0;
} //but, 이 방법은 임의의 자식 프로세스가 종료되지 않으면 wait 함수를 호출한것이 블로킹 상태로 유지됨. 그래서 waitpid 함수를 사용.
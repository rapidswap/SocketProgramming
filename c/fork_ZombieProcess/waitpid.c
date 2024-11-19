#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char*argv[])
{
    int status;
    pid_t pid=fork();

    if(pid==0)
    {
        sleep(15);
        return 24;
    }
    else
    {
        while(!waitpid(-1,&status,WNOHANG)) //종료되지ㅉ 않았으면 3초동안 기다렸다 puts 가나옴
        {
            sleep(3);
            puts("sleep 3sec.");
        }

        if(WIFEXITED(status))
        printf("Child send %d \n",WEXITSTATUS(status));
    }
    return 0; //but, 언제까지 waitpid를 부를수만은 없다. 그래서 시그널핸들링을 사용

}
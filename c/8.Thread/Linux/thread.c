#include <stdio.h>
#include <pthread.h> //쓰레드를 쓰기위한 헤더파일
//컴파일 시 -D_REENTRANT 옵션 사용과 라이브러리 -lpthread 호출
// gcc thread.c -D_REENTRANT -o tr -lpthread
void* thread_summation(void* arg);
int sum=0;

int main(int argc,char* argv[])
{
    pthread_t id_t1, id_t2;
    int range1[]={1,5};
    int range2[]={6,10};

    pthread_create(&id_t1,NULL,thread_summation,(void*)range1); // 마지막 밸류값은 어느 값이 들어갈지 몰라서 void포인터로 보낸거임
    pthread_create(&id_t2,NULL,thread_summation,(void*)range2);

    pthread_join(id_t1, NULL); //쓰레기드가 모드 실행될때까지 대기하려고..
    pthread_join(id_t2,NULL);
    printf("result: %d\n",sum);
    return 0;
}

void* thread_summation(void* arg)
{
    int start=((int*)arg)[0];
    int end=((int*)arg)[1];

    while(start<=end)
    {
        sum+=start;
        start++;
    }
    return NULL;
}
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREAD 100
void* thread_inc(void* arg);
void* thread_des(void* arg);

long long num=0;
pthread_mutex_t mutex; // mutex 생성

int main(int argc,char* argv[])
{
    pthread_t thread_id[NUM_THREAD];
    int i;

    pthread_mutex_init(&mutex,NULL); // 키를 초기화 해준다고 생각

    for(i=0;i<NUM_THREAD;i++)
    {
        if(i%2)
        {
            pthread_create(&(thread_id[i]),NULL,thread_inc,NULL);
        }
        else
        {
            pthread_create(&(thread_id[i]),NULL,thread_des,NULL);
        }
    }

    for(i=0;i<NUM_THREAD;i++)
        pthread_join(thread_id[i],NULL);

    printf("result: %lld\n",num);
    pthread_mutex_destroy(&mutex); //뮤텍스 제거해줘야함
    return 0;
}

void* thread_inc(void* arg)
{
    int i;
    pthread_mutex_lock(&mutex); //사용하고 있어서 문을닫고
    for(i=0;i<50000000;i++)
    {
        num+=1;
    }
    pthread_mutex_unlock(&mutex); //썻으면 다시 열음
    return NULL;
}

void* thread_des(void* arg)
{
    int i;
    pthread_mutex_lock(&mutex);
    for(i=0;i<50000000;i++)
    {
        num-=1;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}
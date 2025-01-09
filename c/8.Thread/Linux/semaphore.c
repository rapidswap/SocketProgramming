#include<stdio.h>
#include<pthread.h>
#include<semaphore.h> //세마포어에서 사용함

void* read(void* arg);
void* accu(void* arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char* argv[])
{
    pthread_t id_t1, id_t2;
    sem_init(&sem_one,0,0); //semone은 두개이상의 쓰레드 접근 가능하게 (0)옵션, 그리고 카운트는 0이라 일단 대기
    sem_init(&sem_two,0,1);

    pthread_create(&id_t1,NULL,read,NULL);
    pthread_create(&id_t2,NULL,accu,NULL);

    pthread_join(id_t1,NULL);
    pthread_join(id_t2,NULL);

    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}

void* read(void* arg)
{
    int i;
    for(i=0;i<5;i++)
    {
        fputs("Input num: ",stdout);

        sem_wait(&sem_two); //two에 카운트가 1이상일때까지 대기
        scanf("%d",&num);
        sem_post(&sem_one); //쓰면 one에게 반납
    }
    return NULL;
}

void* accu(void* arg)
{
    int sum=0,i;
    for(i=0;i<5;i++)
    {

        sem_wait(&sem_one);
        sum+=num;
        sem_post(&sem_two);
    }
    printf("Result: %d\n",sum);
    return NULL;
}
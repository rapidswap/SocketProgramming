#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

void* handle_clnt(void* arg);
void send_msg(char* msg, int len);
void error_handling(char* msg);

int clnt_cnt=0; //쓰레드에서 작동하기 때문에 전역
int clnt_socks[MAX_CLNT]; //위와 동일
pthread_mutex_t mutx; //뮤텍스 선언

int main(int argc,char* argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int clnt_adr_sz;
    pthread_t t_id;
    if(argc!=2)
    {
        printf("Usage: %s <port> \n",argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutx,NULL);
    serv_sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
        error_handling("bind error");
    if(listen(serv_sock,5)==-1)
        error_handling("listen error");

    while(1)
    {
        clnt_adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);

        pthread_mutex_lock(&mutx); //클라이언트 소켓마다 하나씩 접근 해야하므로 뮤텍스
        clnt_socks[clnt_cnt++]=clnt_sock;
        pthread_mutex_unlock(&mutx);

        pthread_create(&t_id,NULL,handle_clnt,(void*)&clnt_sock);
        pthread_detach(t_id);
        printf("Connected client IP: %s \n",inet_ntoa(clnt_adr.sin_addr));
    }
    close(serv_sock);
    return 0;
}

void* handle_clnt(void* arg) //클라이언트 소켓 핸들
{
    int clnt_sock=*((int*) arg); //소켓 정보는 정수형이기 때문에 void로 받은 값을 인트포인터로 강제변환
    int str_len=0,i;
    char msg[BUF_SIZE];

    while((str_len=read(clnt_sock,msg,sizeof(msg)))!=0) //받은 메세지를 보내줌
        send_msg(msg,str_len);
    
    pthread_mutex_lock(&mutx); //핸들 접근시 동기화
    for(i=0;i<clnt_cnt;i++)
    {
        if(clnt_sock==clnt_socks[i])
        {
            while(i++<clnt_cnt-1) //종료되는 소켓을 찾고 앞당겨줌
                clnt_socks[i]=clnt_socks[i+1];
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutx);
    close(clnt_sock);
    return NULL;
}

void send_msg(char* msg, int len) //메세지 전송 함수
{
    int i;
    pthread_mutex_lock(&mutx);
    for(i=0;i<clnt_cnt;i++) //모든 클라이언트에게 받은메세지를 전송해줌
    {
        write(clnt_socks[i],msg,len);
    }
    pthread_mutex_unlock(&mutx);
}

void error_handling(char*message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
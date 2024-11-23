#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define TTL 64 //데이터를 어디까지멀리 보낼까
#define BUF_SIZE 30
void error_handling(char*message);

int main(int argc,char*argv[])
{
    int send_sock;
    struct sockaddr_in mul_adr;
    int time_live=TTL;
    FILE *fp;
    char buf[BUF_SIZE];
    if(argc!=3)
    {
        printf("Usage: %s <group ip> <port> \n",argv[0]);
        exit(1);
    }

    send_sock=socket(PF_INET,SOCK_DGRAM,0);//멀티캐스트는 udp 방식
    memset(&mul_adr,0,sizeof(mul_adr));
    mul_adr.sin_family=AF_INET;
    mul_adr.sin_addr.s_addr=inet_addr(argv[1]);
    mul_adr.sin_port=htons(atoi(argv[2]));
    
    setsockopt(send_sock,IPPROTO_IP,IP_MULTICAST_TTL,(void*)&time_live,sizeof(time_live));
    if((fp=fopen("news.txt","r"))==NULL)
        error_handling("fopen error");

    while(!feof(fp))
    {
        fgets(buf,BUF_SIZE,fp);
        sendto(send_sock,buf,strlen(buf),0,(struct sockaddr*)&mul_adr,sizeof(mul_adr));
        sleep(2);
    }
    close(fp);
    close(send_sock);
    return 0;
}

void error_handling(char*message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
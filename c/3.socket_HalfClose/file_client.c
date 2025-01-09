#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
//파일 디스크립터 하프클로즈 존재
#define BUF_SIZE 30
void error_handling(char*message);

int main(int argc,char*argv[])
{
    int sd;
    FILE *fp;
    char buf[BUF_SIZE];
    int read_cnt;
    struct sockaddr_in serv_adr;
    if(argc!=3)
    {
        printf("Usage: %s <ip> <port> \n",argv[0]);
        exit(1);
    }

    fp=fopen("receive.dat","wb");
    sd=socket(PF_INET,SOCK_STREAM,0);

    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    connect(sd,(struct sockaddr*)&serv_adr,sizeof(serv_adr));

    while((read_cnt=read(sd,buf,BUF_SIZE))!=0)
        fwrite((void*)buf,1,read_cnt,fp);
    puts("Received file data");
    write(sd,"Thank you",10);
    fclose(fp);
    close(sd);
    return 0;
}
void error_handling(char*message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
//이때 윈도우는 다른데
//SD_RECEIVE 입력스트림 종료
//SD_SEND 출력스트림 종료
// SD_BOTH 입출력 스트림 종료이다.
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
void error_handling(char *message);

int main(int argc, char* argv[])
{
    char *addr="127.232.124.79";
    struct sockaddr_in addr_inet;
    if(!inet_aton(addr,&addr_inet.sin_addr))
        error_handling("Conversion error!");
    else
        printf("Network ordered integer addr: %#x \n",addr_inet.sin_addr.s_addr);
    return 0;
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
} //즉 aton은 쉽게 문자열을 정수형으로 바꿔준다고 생각


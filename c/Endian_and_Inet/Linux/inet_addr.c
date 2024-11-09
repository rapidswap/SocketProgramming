#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
    char *addr1="1.2.3.4";
    char *addr2="1.2.3.256";

    unsigned long conv_addr=inet_addr(addr1);
    if(conv_addr==INADDR_NONE)
        printf("Error occured!\n");
    else
        printf("Network ordered integer addr: %#lx \n",conv_addr);

    conv_addr=inet_addr(addr2);
    if(conv_addr==INADDR_NONE)
        printf("Error occured!\n");
    else
        printf("Network ordered integer addr: %#lx \n",conv_addr);
    return 0;
} //우리가 알기 쉬운 주소를 32비트 정수형으로 바꾸어 구조체 sockaddr_in에게 주소값을 전달하기 위해서.
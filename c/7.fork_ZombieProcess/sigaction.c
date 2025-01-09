//sigaction은 UNIX 운영체제에서 동작방식에 차이가없다!
//그리고 signal 보다 훨씬 안정적..!
 #include<stdio.h>
 #include<unistd.h>
 #include<signal.h>

 void timeout(int sig)
 {
    if(sig==SIGALRM)
        puts("Time out!");
    alarm(2);
 }

 int main(int argc,char*argv[])
 {
    int i;
    struct sigaction act;
    act.sa_handler=timeout; //함수정보가 담기는곳
    sigemptyset(&act.sa_mask); // 구조체 안에 다른 것은 초기화
    act.sa_flags=0;
    sigaction(SIGALRM,&act,0);//알람 신호가 오면 act안에 timeout을 실행시켜라
    alarm(2);

    for(i=0;i<3;i++)
    {
        puts("wait..");
        sleep(100); //결국엔 이건 실행안됨 3번반복해줘서
    }
    return 0;
 }
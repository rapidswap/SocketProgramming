# TCP/IP 소켓 프로그래밍

## 네트워크 프로그래밍

네트워크로 연결된 서로 다른 컴퓨터들이 서로 데이터를 주고 받는 것, 물리적 연결 필수 => 인터넷이라는 물리적 연결이 되어있다.

**!! 소프트웨어적으로 데이터 송신을 도와주는 것이 소켓(Socket)이고 이 소켓은 운영체제에서 제공해준다.**
* 소켓) 네트워크망에 접속하기 위한 도구로 두 컴퓨터 간 연결을 의미한다.
  * _예) 전화망을 통한 목소리 전달하는 전화기가 Socket_

1. 소켓 생성은 int socket(int domain, int type, int protocol)로 호출하며 성공시 파일 디스크립터, 실패시 -1을 반환 하게 된다.
2. bind 호출 int bind(int fockfd, struct sockaddr* myaddr, socklen_t addrlen), 성공시 0 실패시 -1
3. listen 호출 int listen(int sockfd, int backlog) 성공시 0 실패시 -1
4. accept 호출 int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen) 성고시 파일 디스크립터, 실패시 -1
5. > 요약: 1. 소켓 생성
   > 2. IP주소와 PORT 번호 할당
   > 3. 연결 요청 가능상태 변경
   > 4. 연결 요청에 대한 수락
   >    즉, 서버 소켓은 리스닝 소켓, 연결요청은 클라이언트 소켓
 

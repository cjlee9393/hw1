
// * client에서는 server와 connection establish
// 다음 즉시 10 바이트 데이터 3개를 server에 전송
// (예를 들면 0123456789, ABCDEFGHIJ, KLMNOPQRST)
// 3번의 send() 함수 이용하여 전송함





#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024

char data1[] = "0123456789";
char data2[] = "ABCDEFGHIJ";
char data3[] = "KLMNOPQRST";

int main(int argc, char * argv[]){
    // init
    int clnt_sock;

    struct sockaddr_in serv_addr;

    char buf[BUF_SIZE];

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // socket
    clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1)
        printf("error in socket");

    // connect
    if (connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        printf("error in connect");

    send(clnt_sock, data1, sizeof(data1), 0);
    send(clnt_sock, data2, sizeof(data2), 0);
    send(clnt_sock, data3, sizeof(data3), 0);

    // 그 다음부터는 터미널로부터 입력된 데이터를 server에 전송함.
    // (수업의 예에서 처럼 사용자를 ‘q’를 입력하면 client 프로그램을 종료시킴.)
    while(1){
	printf("send message: ");
	fgets(buf, sizeof(buf), stdin);

	// if q or Q, break
    if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
        break;

	send(clnt_sock, buf, strlen(buf), 0);
}
    
    // close
    close(clnt_sock);
}
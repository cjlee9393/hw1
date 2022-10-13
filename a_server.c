







// 동일한 형태로 수신한 데이터를 읽어서 화면에 출력하는 동작을 반복함.

// Client가 종료되면 server도 종료시킴.

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

int error_handling(char * message);

int main(int argc, char * argv[]){
    // init
    int serv_sock;
    int clnt_sock;
    int state;
    int rcv_buf = 100;
    socklen_t len;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    char message[BUF_SIZE];
    // char message2[BUF_SIZE];
    // char message3[BUF_SIZE];

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    socklen_t clnt_addr_size;

    // socket
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        printf("error in socket");

    // bind
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        printf("error in bind");

    // listen
    if (listen(serv_sock, 5) == -1)
        printf("error in listen");

    // accept
    // * Server는 client 와 connection establish를 함.
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    // 최대 buffer 크기가 100 바이트인 버퍼를 이용하여 읽음.
    state = setsockopt(clnt_sock, SOL_SOCKET, SO_SNDBUF, (void*)&rcv_buf, sizeof(rcv_buf));
	if(state)
		error_handling("error in setsockopt()");

    len = sizeof(rcv_buf);
    state = getsockopt(clnt_sock, SOL_SOCKET, SO_SNDBUF, (void*)&rcv_buf, &len);
	if(state)
		error_handling("error in getsockopt()");

    printf("clnt_sock input buffer size: %d \n", rcv_buf);

    // * 5초 동안 sleep
    sleep(5);

    // 읽은 데이터를 화면에 출력시킴. (recv() 이용하여 데이터 읽음.)
    // read and write
    int str_len;
    while((str_len=recv(clnt_sock, message, sizeof(message), 0))!=0){
        for (int i=0; i<str_len; i++){
            if (message[i] == '\0'){
                putchar('\n');
            }else{
                putchar(message[i]);
            }
            fflush(stdout);
        }
    }

    /*int str_len;
    str_len = recv(clnt_sock, message, sizeof(message), 0);
    if (str_len > 0){
        message[str_len] = 0;
        printf("%s\n", message);
    }*/

    // close
    close(clnt_sock);
    close(serv_sock);
}

int error_handling(char * message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
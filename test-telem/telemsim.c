#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <assert.h>

#define SA struct sockaddr

void swap_end_4b(char* p)
{
    char a, b, c, d;
    a = p[0];
    b = p[1];
    c = p[2];
    d = p[3];

    p[0] = d;
    p[1] = c;
    p[2] = b;
    p[3] = a;
}

void health_pkt(char* buf)
{
    *((int*)(buf + 0)) = 16;
    *((int*)(buf + 4)) = 4;
    *((float*)(buf + 8)) = 6.9f;
    *((float*)(buf + 12)) = 4.20f;
    *((float*)(buf + 16)) = 77.0f;

    swap_end_4b(buf + 0);
    swap_end_4b(buf + 4);
    swap_end_4b(buf + 8);
    swap_end_4b(buf + 12);
    swap_end_4b(buf + 16);
}

void handler(int sockfd)
{
    char buf[1024];
    int n;

    for (;;)
    {
        bzero(buf, 1024);
        health_pkt(buf);
        //printf("length: %d\n", *((int*)(buf)));
        write(sockfd, buf, 20);
        //write(sockfd, buf, 1024);
        sleep(1);
    }
}

int main(int argc, char** argv)
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) exit(1);
    
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8888);

    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
    {
        exit(1);
    }

    if ((listen(sockfd, 5)) != 0)
    {
        exit(1);
    }

    len = sizeof(cli);

    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0)
    {
        exit(1);
    }

    handler(connfd);

    close(sockfd);

    return 0;
}

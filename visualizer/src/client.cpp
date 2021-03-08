#include "client.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

static std::vector<float> last_packet;
static int sfd;

void Client::con()
{
    int sockfd, portno, n;          // file descriptor
                                    // port number of server accepting connections
                                    // return value for read/write
    struct sockaddr_in serv_addr;   // address of server
    struct hostent *server;         // pointer to struct in netdb.h

    char buffer[256];

    // portno = atoi(argv[2]);
    portno = 1234;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        printf("ERROR opening socket\n");

    server = gethostbyname("localhost");
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
    serv_addr.sin_port = htons(portno);

    int err = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (err < 0)
    {
        printf("not working!\n");
    }
    else
    {
        printf("ok!\n");
    }

    /*if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);*/

    sfd = sockfd;
}

static void handle()
{
    // sfd is the socket
}

void Client::disconnect(int sockfd)
{
    close(sockfd);
}

std::vector<float> Client::getPacket()
{
    return last_packet;
}

// #ifdef main
// #undef main
// #endif
// int main(int argc, char *argv[])
// {
//     Client::con();

//     return 0;
// }


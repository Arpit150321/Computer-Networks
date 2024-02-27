/*

Argument parameter: filename IpAddress portnumber

argv[0] = filename
argv[1] = IpAddress
argv[2] = portnumber

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
void main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage %s hostname port", argv[0]);
        exit(1);
    }

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("Error opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL)
        error("Server is not found!");

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, sizeof(serv_addr));
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)serv_addr, sizeof(serv_addr)) < 0)
        error("Connection failed");

        close(sockfd);
}
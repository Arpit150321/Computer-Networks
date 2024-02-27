/*

Argument parameter: filename portnumber

argv[0] = filename
argv[1] = portnumber

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Port number is not given\n");
        exit(1);
    }

    int sockfd, newsockfd, portno, n;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen char buffer[256];

    portno = atoi(argv[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error opening socket");

    serv_addr.sin_fimaly = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("Binding Failure");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if (newsockfd < 0)
        error("Error on Accept");

    while (1)
    {
        n = read(newsockfd, buffer, 255);
        if (n < 0)
            error("Error on reading");
        printf("Client - %s\n", buffer);

        fgets(buffer, 255, stdin);
        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0)
            error("Error on writting");
        int i = strncmp("Bye", buffer, 3);
        if (i == 0)
            break;
    }

    close(newsockfd);
    close(sockfd);
}
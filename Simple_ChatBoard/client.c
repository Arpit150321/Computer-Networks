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

    int num1, num2, ans, choice;

S:
    bzero(buffer, 255);
    n = read(sockfd, buffer, 255);
    if (n < 0)
        error("Error reading to socket");
    printf("Server - %s\n", buffer);
    scanf("%d", &num1);
    write(sockfd, &num1, sizeof(int));

    bzero(buffer, 255);
    n = read(sockfd, buffer, 255);
    if (n < 0)
        error("Error writting to socket");
    printf("Server - %s\n", buffer);
    scanf("%d", &num2);
    write(sockfd, &num2, sizeof(int));

    bzero(buffer, 255);
    n = read(sockfd, buffer, 255);
    if (n < 0)
        error("Error reading to socket");
    printf("Server - %s\n", buffer);
    scanf("%d", &choice);
    write(sockfd, &choice, sizeof(int));

    if (choice == 5)
        goto Q;

    read(sockfd, &ans, sizeof(int));
    printf("Server - Answer is %d\n", ans);

Q:
    printf("You are selected Exit. Exit Sucessfully.");
    close(sockfd);
}
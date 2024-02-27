/*
Server Code
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

    int num1, num2, ans, choice;

s:
    n = write(newsockfd, "Enter the number 1: ", sizeof("Enter the number 1: "));
    if (n < 0)
        error("Error writting to socket");
    read(newsockfd, &num1, sizeof(int));
    printf("Client - Number 1 is %d\n", num1);

    n = write(newsockfd, "Enter the number 2: ", sizeof("Enter the number 2: "));
    if (n < 0)
        error("Error writting to socket");
    read(newsockfd, &num2, sizeof(int));
    printf("Client - Number 2 is %d\n", num2);

    n = write(newsockfd, "1. Addition \n2. Substraction \n3. Multiplication \n4. Devision \n5. Exit\n", sizeof("1. Addition \n2. Substraction \n3. Multiplication \n4. Devision \n5. Exit\n"));
    if (n < 0)
        error("Error writting to socket");
    read(newsockfd, &choice, sizeof(choice));
    printf("Client - Choice is %d\n", choice);

    switch (choice)
    {
    case 1:
        ans = num1 + num2;
        break;
    case 2:
        ans = num1 - num2;
        break;
    case 3:
        ans = num1 * num2;
        break;
    case 4:
        ans = num1 / num2;
        break;
    case 5:
        goto Q;
        break;
    }

    write(newsockfd, &ans, sizeof(int));
    if (choice != 5)
        goto S;

Q:
    close(newsockfd);
    close(sockfd);
    return 0;
}
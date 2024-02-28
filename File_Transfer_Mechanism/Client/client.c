/*
Client code
Argument parameter: filename IpAddress portnumber

argv[0] = filename
argv[1] = IpAddress
argv[2] = portnumber

*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		fprintf(stderr, "Usage %s hostname port\n", argv[0]);
		exit(1);
	}
	
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	char buffer[256];
	
	portno = atoi(argv[2]);
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("Error opening Socket");
	
	server = gethostbyname(argv[1]);
	if(server == NULL)
	{
		fprintf(stderr, "No such host");
	}
	
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = PF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Connection Failed");

    write(sockfd, "GET", 3);

    FILE *fp;

    int ch = 0;
    fp = fopen("smaple_out.txt", "a");
    int words;

    read(sockfd, &words, sizeof(int));

    while(ch != words){
        read(sockfd, buffer, 255);
        fprintf(fp, "%s", buffer);
        ch ++;
    }

    printf("The file has been transfered succefully. It is saved by name sample_out.txt");

    close(sockfd);

    return 0;
}
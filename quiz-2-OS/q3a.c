#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char stringbuff[500];
	struct sockaddr_in	 servaddr; 

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{ 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n, len; 
	FILE *fp = fopen("para1.txt","r");
	char chbuf[500];
	while(fscanf(fp, "%s", chbuf) != EOF )
	{
		strcpy(stringbuff,chbuf);
		sendto(sockfd, (const char *)stringbuff, strlen(stringbuff), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	}

	strcpy(stringbuff,"\n\n");
	sendto(sockfd, (const char *)stringbuff, strlen(stringbuff), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	
	close(sockfd); 
	return 0; 
} 

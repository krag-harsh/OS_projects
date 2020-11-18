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
	struct sockaddr_in servaddr, cliaddr; 
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))< 0) 
	{ 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int len, n; 
	len = sizeof(cliaddr); 
	int countoffile=0;
	for(;;)
	{
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
		buffer[n] = '\0'; 
		if(strcmp(buffer,"\n\n")!=0)
		printf("%s ",buffer);
		else		//remove this else statement if want to check for two files simultaneously.(hardcoded for 2 files)
		{
			break;
		}
		

		int toend = strcmp(buffer,"\n\n");
		if (toend == 0)
		countoffile++;
		if(countoffile>1)
		break;
		
	}
	return 0; 
} 

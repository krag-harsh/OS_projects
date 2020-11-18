#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main() 
{ 

	int fd1[2]; 
	int fd2[2]; 

	char strinput[500]; 
	pid_t p; 
	pipe(fd1);
	pipe(fd2);
 
	fgets(strinput, 500, stdin); 
   	//printf("entered string: %s\n", strinput); 
	p = fork(); 
	if (p < 0) 
	{ 
		fprintf(stderr, "fork Failed" ); 
		return 1; 
	} 

	// Parent process 
	else if (p > 0) 
	{ 
		char finalstr[500]; 
		close(fd1[0]); 
		write(fd1[1], strinput, strlen(strinput)+1); 
		close(fd1[1]); 

		wait(NULL); 	//wait for child process to complete

		close(fd2[1]);
		read(fd2[0], finalstr, 500); 		//read string from child
		printf("%s\n", finalstr); 
		close(fd2[0]); 
	} 

	// child process 
	else
	{ 
		close(fd1[1]);

		char finalstr[500]; 
		read(fd1[0], finalstr, 500); //read the sent data
		int k = strlen(finalstr); 
		for (int i = 0; finalstr[i]!='\0'; i++) 
		{
			if(finalstr[i]=='\\' && finalstr[i+1]!='\0')
			{
				if(finalstr[i+1]=='a' || finalstr[i+1]=='b' || finalstr[i+1]=='f' || finalstr[i+1]=='n' || finalstr[i+1]=='r' || finalstr[i+1]=='t' || finalstr[i+1]=='v')
				{
					i++;
					continue;
				}
			}
			else if(finalstr[i] >= 'a' && finalstr[i] <= 'z') 
			{
				finalstr[i] = finalstr[i]-32;
			}
		}

		finalstr[k] = '\0';

		close(fd1[0]); 
		close(fd2[0]); 

		write(fd2[1], finalstr, strlen(finalstr)+1); 
		close(fd2[1]); 

		exit(0); 
	} 
} 

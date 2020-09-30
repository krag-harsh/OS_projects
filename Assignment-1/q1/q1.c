#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t pid;
	pid=fork();

	if(pid<0){
		fprintf(stderr, "Ford Filed");
		printf("Fork failed");
	}
	else if(pid ==0)
	{
		printf("In child process\n");
		FILE* stream = fopen("file_modified.csv", "r");
		char line[1024];
		printf("Average marks of each student of section A :\n");
		char che[2];
		strcpy(che,"A");
		char *backup;
		while (fgets(line, 1024, stream))
		{
			char* tmp = strdup(line);
			char *token = strtok(tmp," "); 
			while (token != NULL) 
			{
				int ret=strcmp(che,token);
				if(ret==0)
				{
					token = strtok(NULL, " ");
					int sum=0;
					for(int i=0;i<3;i++)
					{
						int marks= atoi(token);
						sum+=marks;
						token = strtok(NULL, " ");
					}
					int m=atoi(token);
					sum+=m;
					float f=sum/4.0f;
					printf("Student ID: %s Average marks = %.2f\n",backup,f);
				}
				else{
					backup=token;
					token = strtok(NULL, " "); 
				}	
			} 
			free(tmp);
		}
		exit(1);
	}
	else
	{
		waitpid(-1, NULL , 0);
		printf("\n\nChild complete\n");
		FILE* stream = fopen("file_modified.csv", "r");
		char line[1024];
		printf("\nAverage marks of each student of section B :\n\n");
		char che[2];
		strcpy(che,"B");
		char *backup;
		while (fgets(line, 1024, stream))
		{
			char* tmp = strdup(line);
			char *token = strtok(tmp," "); 
			while (token != NULL) 
			{
				int ret=strcmp(che,token);
				if(ret==0)
				{
					token = strtok(NULL, " ");
					int sum=0;
					for(int i=0;i<3;i++)
					{
						int marks= atoi(token);
						sum+=marks;
						token = strtok(NULL, " ");
					}
					int m=atoi(token);
					sum+=m;
					float f=sum/4.0f;
					printf("Student ID: %s Average marks = %.2f\n",backup,f);
				}
				else{
					backup=token;
					token = strtok(NULL, " "); 
				}
				
			} 
			free(tmp);
		}

	}
	return 0;
}
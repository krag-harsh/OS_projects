#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
//#include<readline/readline.h>
#include<readline/readline.h> 
#include <sys/wait.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>


char **get_array(char *input) {

	// if (strlen(input) != 0) 
	// 	add_history(input);

    char **command = malloc(10 * sizeof(char *));
    if (command == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    char *separator = " ";
    char *token;
    int i = 0;

    token = strtok(input, separator);
    while (token != NULL) {
        command[i] = token;
        i++;

        token = strtok(NULL, separator);
    }

    command[i] = NULL;
    return command;
}


int main()
{
	pid_t pid;
	// pid=fork();
	// if(pid<0){
	// 	fprintf(stderr, "Fork Filed");
	// 	return 1;
	// }
	// else if(pid ==0)
	// {
	// 	printf("In child process\n");
	// 	printf("\n");
	// 	char *arr[]={"harsh","ajie","hahaha",NULL};
	// 	execv("./try",arr);
	// 	exit(1);
	// }
	// else
	// {
	// 	//waitpid(-1, NULL , 0);
	// 	wait(NULL);	
	// 	printf("\nChild complete\n");
	// }

	char input[100];
	//char *input;
	char **comarray;
	while(1)
	{
		printf("Harsh@terminal>>>");
		//input = (char*)malloc(sizeof(char*)*100);
		//fgets(input,100,stdin);
		gets(input);
		comarray=get_array(input);
		// if(!comarray[0])
		// {
		// 	free(comarray);
		// 	printf("here");
		// 	continue;
		// }

//internal commands:
		if(strcmp("cd", comarray[0]) == 0 )
		{
			//chdir("..");
			chdir(comarray[1]);
		}

		if(strcmp("echo", comarray[0]) == 0 )
		{
			if(comarray[1]!=NULL)		//error handling for empty
			{
				if(strcmp("-n",comarray[1])==0)
				{
					int i=2;
					while(comarray[i]!=NULL)
					{
						printf("%s ",comarray[i]);
						i++;
					}

				}

				else
				{
					int i=1;
					while(comarray[i]!=NULL)
					{
						printf("%s ",comarray[i]);
						i++;
					}
					printf("\n");
				}
			}
		}

		if(strcmp("history", comarray[0]) == 0 )
		{
			printf("\n\tThank You!!!\n");
		}


		if(strcmp("pwd", comarray[0]) == 0 )
		{
			char *adde=(char *)malloc(500*sizeof(char));
			getcwd(adde,500);
			printf("%s \n",adde);
		}


		if(strcmp("exit", comarray[0]) == 0 )
		{
			printf("\n\t\tThank You!!!\n");
			exit(0);
			break;

		}
	//external commands:

		if(strcmp("ls", comarray[0]) == 0 )
		{
			pid=fork();
			if(pid<0){
				fprintf(stderr, "Fork Filed");
				return 1;
			}
			else if(pid ==0)
			{
				execv("./ls",comarray);
			}
			else
			{
				waitpid(-1, NULL , 0);
			}
		}


		if(strcmp("cat", comarray[0]) == 0 )
		{
			pid=fork();
			if(pid<0){
				fprintf(stderr, "Fork Filed");
				return 1;
			}
			else if(pid ==0)
			{
				execv("./cat",comarray);
			}
			else
			{
				waitpid(-1, NULL , 0);
			}
			
		}


		if(strcmp("date", comarray[0]) == 0 )
		{
			pid=fork();
			if(pid<0){
				fprintf(stderr, "Fork Filed");
				return 1;
			}
			else if(pid ==0)
			{
				execv("./date",comarray);
			}
			else
			{
				waitpid(-1, NULL , 0);
			}
		}

		if(strcmp("rm", comarray[0]) == 0 )
		{
			pid=fork();
			if(pid<0){
				fprintf(stderr, "Fork Filed");
				return 1;
			}
			else if(pid ==0)
			{
				execv("./rm",comarray);
			}
			else
			{
				waitpid(-1, NULL , 0);
			}
		}


		if(strcmp("mkdir", comarray[0]) == 0 )
		{
			pid=fork();
			if(pid<0){
				fprintf(stderr, "Fork Filed");
				return 1;
			}
			else if(pid ==0)
			{
				execv("./mkdir",comarray);
			}
			else
			{
				waitpid(-1, NULL , 0);
			}
		}



	}

	return 0;
}
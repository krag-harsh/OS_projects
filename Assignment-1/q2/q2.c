#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
//#include<readline/readline.h>
#include<readline/readline.h> 
#include <sys/wait.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>


char **get_input(char *input) {

	// if (strlen(input) != 0) 
	// 	add_history(input);

    char **command = malloc(10 * sizeof(char *));
    if (command == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}


int main()
{
	// pid_t pid;
	// pid=fork();

	// if(pid<0){
	// 	fprintf(stderr, "Fork Filed");
	// 	return 1;
	// }
	// else if(pid ==0)
	// {
	// 	printf("In child process\n");
	// 	printf("\n");
	// 	char *arr[]={"harsh","ajie",NULL};
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
	char **comarray;
	while(1)
	{
		printf("Harsh@terminal>>>");
		//fgets(input,100,stdin);
		gets(input);
		comarray=get_input(input);
		if(!comarray[0])
		{
			free(comarray);
			printf("here");
			continue;
		}

//internal commands:
		if(strcmp("cd", comarray[0]) == 0 )
		{
			printf("\n\tThank You!!!\n");
		}

		if(strcmp("echo", comarray[0]) == 0 )
		{
			printf("\n\tThank You!!!\n");
		}

		if(strcmp("history", comarray[0]) == 0 )
		{
			printf("\n\tThank You!!!\n");
		}


		if(strcmp("pwd", comarray[0]) == 0 )
		{
			printf("\n\tThank You!!!\n");
		}


		if(strcmp("exit", comarray[0]) == 0 )
		{
			printf("\n\tThank You!!!\n");
			exit(0);
			break;

		}
//external commands:

		//break;

	}


	return 0;
}
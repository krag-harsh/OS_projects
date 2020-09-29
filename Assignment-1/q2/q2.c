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

	//char input[100];
	char *input;
	char **comarray;
	char *currentpath=(char *)malloc(500*sizeof(char));

	getcwd(currentpath,500);
	char ls[500] = "/ls";
	strcat(currentpath,ls);
	strcpy(ls,currentpath);
	
	getcwd(currentpath,500);
	char catadd[500] = "/cat";
	strcat(currentpath,catadd);
	strcpy(catadd,currentpath);

	getcwd(currentpath,500);
	char dadd[500] = "/date";
	strcat(currentpath,dadd);
	strcpy(dadd,currentpath);

	getcwd(currentpath,500);
	char runadd[500] = "/rm";
	strcat(currentpath,runadd);
	strcpy(runadd,currentpath);

	getcwd(currentpath,500);
	char mkdd[500] = "/mkdir";
	strcat(currentpath,mkdd);
	strcpy(mkdd,currentpath);

	getcwd(currentpath,500);
	char hiaddress[500] = "/history.txt";
	strcat(currentpath,hiaddress);
	strcpy(hiaddress,currentpath);

	getcwd(currentpath,500);

	//printf("%s",ls);
	while(1)
	{
		printf("Harsh@terminal>>>");
		input = (char*)malloc(sizeof(char*)*100);
		//fgets(input,100,stdin);
		gets(input);
		if(strlen(input)==0)
		continue;
		

		char *toadd=(char *)malloc(500*sizeof(char));
		strcpy(toadd,input);

		FILE *fptr;
		// fptr=fopen("history.txt","a");
		fptr=fopen(hiaddress,"a");
		fputs(toadd,fptr);
		fputs("\n",fptr);
		fclose(fptr);

		comarray=get_array(input);
		// if(!comarray[0])
		// {
		// 	free(comarray);
		// 	printf("here");
		// 	continue;
		// }

	//internal commands:--------------------------------------
		if(strcmp("cd", comarray[0]) == 0 )
		{
			if(comarray[1]==NULL)
			chdir(getenv("HOME"));
			else if (strcmp("~", comarray[1]) == 0 )
			{
				chdir(getenv("HOME"));
			}
			else if (strcmp("--help", comarray[1]) == 0 )
			{
				printf("Change the shell working directory.\n");
			}
			//chdir("..");
			else
			{
				chdir(comarray[1]);
			}
			
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

				else if (strcmp("-E",comarray[1])==0)
				{
					int i=2;
					while(comarray[i]!=NULL)
					{
						// for(int j=0;j<strlen(comarray[i]);j++)
						// {
						// 	//if(comarray[j][i]!='\\')
						// 	printf("%s",comarray[j][i]);
						// }
						printf("%s ",comarray[i]);
						i++;
					}
					printf("\n");
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
			//printf("\n\t Working on this feature\n");
			if(comarray[1]==NULL)
			{
				FILE* stream = fopen(hiaddress, "r");
				char line[1024];
				int count=1;
				while (fgets(line, 1024, stream))
				{
					char* tmp = strdup(line);
					printf("%d  %s",count,tmp);
					count++;
				}
				fclose(stream);

			}
			else if (strcmp("-w", comarray[1]) == 0)
			{
				FILE *fptr1, *fptr2;
				fptr1 = fopen(hiaddress,"r");
				fptr2 = fopen("historyfile.txt","a");
				char line[1024];
				int count=1;
				while (fgets(line, 1024, fptr1))
				{
					char* tmp = strdup(line);
					//printf("%d  %s",count,tmp);
					fprintf(fptr2,tmp);
					count++;
				}
				fclose(fptr1);
				fclose(fptr2);
				
			}
			
			else if (strcmp("-c", comarray[1]) == 0)
			{
				FILE *fptr;
				fptr = fopen(hiaddress,"w");
				fprintf(fptr,"");
				fclose(fptr);

			}
			
		}


		if(strcmp("pwd", comarray[0]) == 0 )
		{
			if(comarray[1]!=NULL)
			{
				if(strcmp("-P", comarray[1]) == 0 )
				{
					char *adde=(char *)malloc(500*sizeof(char));
					getcwd(adde,500);
					printf("%s \n",adde);
				}

				else if(strcmp("--help", comarray[1]) == 0 )
				{
					printf("pwd:\tPrint the name of the current working directory.\nOptions:\n-P\tprint the physical directory, without any symbolic links\n");
				}
			}
			else
			{
				//printf("%s\n",getenv("PWD"));
				char *adde=(char *)malloc(500*sizeof(char));
				getcwd(adde,500);
				printf("%s \n",adde);
			}
		}


		if(strcmp("exit", comarray[0]) == 0 )
		{
			if(comarray[1]!=NULL)
			{
				printf("exit:\n\tExit the shell\n");
				continue;
			}
			printf("\n\t\tThank You!!!\n\n");
			exit(0);
			break;

		}
	//external commands:--------------------------------------

		if(strcmp("ls", comarray[0]) == 0 )
		{
			pid=fork();
			if(pid<0){
				fprintf(stderr, "Fork Filed");
				return 1;
			}
			else if(pid ==0)
			{
				//execv("./ls",comarray);
				execv(ls,comarray);
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
				// execv("./cat",comarray);
				execv(catadd,comarray);
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
				// execv("./date",comarray);
				execv(dadd,comarray);
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
				// execv("./rm",comarray);
				execv(runadd,comarray);
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
				// execv("./mkdir",comarray);
				execv(mkdd,comarray);
			}
			else
			{
				waitpid(-1, NULL , 0);
			}
		}



	}

	return 0;
}
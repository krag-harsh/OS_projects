


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int n=10;      //global variable


int main()
{
   printf("hi\n");
   pid_t pid;
	pid=fork();

   // pid_t pid=fork();

	if(pid<0){
		fprintf(stderr, "Ford Filed");
	}
	else if(pid ==0)
	{
		printf("In child process\n");
      while(n>-90)
      {
         n--;
         printf("%d\n",n);
      }
   }
   else
   {
      waitpid(-1, NULL , 0);
      printf("Inside parent process\n");
      while (n<100)
      {
         n++;
         printf("%d\n",n);
      }
   }


   return 0;
}
   
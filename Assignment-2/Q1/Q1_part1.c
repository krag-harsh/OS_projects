/* Name: Harsh Kumar Agarwal
   Roll_Number: 2019423 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int n=10;      //global variable


int main()
{
   pid_t pid;
	pid=fork();

	if(pid<0){
		fprintf(stderr, "Ford Filed");
	}
	else if(pid ==0)
	{
		printf("In child process\n");
      //while(n>-90)
      for(int i=0;i<90;i++)
      {
         n--;
         //printf("%d\n",n);
      }
      printf("Value of n inside child process after reducing 90: %d\n\n", n);
   }
   else
   {
      waitpid(-1, NULL , 0);
      printf("Inside parent process\n");
      //while (n<100)
      for(int i=0;i<90;i++)
      {
         n++;
         //printf("%d\n",n);
      }

      printf("Final value of n inside after parent process after increasing 90: %d\n", n);
   }


   return 0;
}

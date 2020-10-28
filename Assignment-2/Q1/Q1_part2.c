/* Name: Harsh Kumar Agarwal
   Roll_Number: 2019423 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h> 

int n=10;      //global variable

void *workinthread(void *arg)
{
   printf("In child thread process\n");
     // while(n>-90)
   for(int i=0;i<90;i++)
   {
      n--;
      //printf("%d\n",n);
   }
   printf("Value of n inside thread process after reducing 90: %d\n", n);

}


int main()
{

   pthread_t newthread;
   pthread_create(&newthread, NULL, workinthread, NULL);
   //pthread_exit(NULL);

   printf("\nInside parent process\n");
   //while (n<100)
   for(int j=0;j<90;j++)
   {
      n++;
      //printf("%d\n",n);
   }

   printf("Final value of n inside after parent process after increasing 90: %d\n\n", n);

   pthread_join(newthread,NULL);
   
   return 0;
}

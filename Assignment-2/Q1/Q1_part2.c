/* Name: Your Name
   Roll_Number: Your Roll_Number */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h> 

int n=10;

void *workinthread(void *arg)
{
   printf("In child process\n");
      while(n>-90)
      {
         n--;
         printf("%d\n",n);
      }

}


int main()
{


   pthread_t newthread;
   pthread_create(&newthread, NULL, workinthread, NULL);
   //pthread_exit(NULL);

   printf("Inside parent process\n");
   while (n<100)
   {
      n++;
      printf("%d\n",n);
   }

   pthread_join(newthread,NULL);
   
   return 0;
}

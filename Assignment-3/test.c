#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main()
{
	printf("pid of current process(parent)=%d \n",getpid());
	clock_t start, end;
	double TimeUsed;
	int stime;
	printf("Enter value of rtnice(soft real time) \n");
	scanf("%d", &stime);
	printf("value entered = %d\n",stime);
	if(stime<0)
	{
		printf("ERROR: Value cannot be negative\n");
		return 0;
	}

	if(stime>100)
	{
		printf("The value entered is more than 100, therefore terminating the program\n");
		return 0;
	}
	
	// start=clock();

	int pid=fork();
	if(pid==0)
	{
		// printf("before sys call");
		//syscall(548,getpid(),10);
		int r= syscall(548,getpid(),stime);
		if(r==-1)
		{
			printf("PID was not found \n");

		}
		else if(r!=0)
		{
			printf("value returned = %d\n",r );
			printf("error found: %s\n",strerror((int)r) );
		}

		else
		{
			printf("%d value of getpid inside child process\n", getpid());	
		// printf("\nafter sys call\n");	
		start=clock();
		for(int i=0;i<100000000;i++);
		end=clock();
		TimeUsed=((double)(end-start))/CLOCKS_PER_SEC;
		printf("cpu time used by child process= %f ms\n", TimeUsed*1000);
		}
	}
	else if(pid>0)
	{
		// wait(NULL);
		//syscall(548,getpid(),10);
		start=clock();
		for(int i=0;i<100000000;i++);
		end=clock();
		TimeUsed=((double)(end-start))/CLOCKS_PER_SEC;
		printf("cpu time used by parent process= %f ms\n", TimeUsed*1000);
		wait(NULL);

	}
	else
	{
		printf("ERROR while forking\n");
	}

	return 0;
}

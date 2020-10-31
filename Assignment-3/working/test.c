#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main()
{
	printf("pid of current process=%d \n",getpid());
	clock_t start, end;
	double TimeUsed;
	

	int pid=fork();
	if(pid==0)
	{
		start=clock();
		int p=1;
		for(int i=1;i<2000000000;i++);
			//p+=i;

		end=clock();

		TimeUsed=((double)(end-start))/CLOCKS_PER_SEC;
		printf("cpu time used by child process= %f sec\n", TimeUsed);
	}
	else if(pid>0)
	{
		wait(NULL);
		syscall(548,getpid(),3);
		start=clock();
		int p=1;
		for(int i=1;i<2000000000;i++);
			//p+=i;

		end=clock();

		TimeUsed=((double)(end-start))/CLOCKS_PER_SEC;
		printf("cpu time used by parent process= %f sec\n", TimeUsed);
		//

	}
	else
	{
		printf("ERROR while forking\n");
	}

	return 0;
}
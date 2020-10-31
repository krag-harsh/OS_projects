#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <string.h>
#include <time.h>

int main()
{
	long x,x1,x2;
	printf("pid of current process=%ld \n",getpid());
	syscall(548,getpid(),2);

	return 0;
}
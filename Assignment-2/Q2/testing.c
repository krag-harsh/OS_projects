#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/signal.h>
#include <linux/errno.h>
#include <stdio.h>

int main(){
	// int p;
	// char *f;
	//printf("current PID in per d format is: %d\n",getpid());
	printf("PID 1 in per ld format is: %ld\n",1);
	// printf("Try path : /home/harsh\n");

	// printf("enter PID: \n");
	// scanf("%d", &p);
	// printf("Enterr file path\n");
	// scanf("%s",f);

	long int val = syscall(548,1,"/home/harsh/output.txt");
	//int stat=0;

	if(val==0)
	{
		printf("no error\n");
	}
	else{
		printf("error found\n");
	}
	return 0;
}

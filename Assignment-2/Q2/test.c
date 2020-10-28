#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int p;
	char *f;
	f=(char*)malloc(sizeof(char*)*100);
	//printf("current program PID is: %d\n",getpid());
	// printf("Try path : /home/harsh\n");

	printf("enter PID: \n");
	scanf("%d", &p);
	printf("Enter file name\n");
	scanf("%s",f);
	// gets(f);

	// long int val = syscall(548,1,"/home/harsh/output.txt");
	// long int val = syscall(548,5,"/home/harsh/output.txt");
	// long int val = syscall(548,2,"output.txt");

	//printf("value entered %d and %s \n",p,f);

	// f[strcspn(f,"\n")]=0;


	// printf("value entered %d and %s \n",p,f);
	long int val = syscall(548,p,f);

	if(val==0)
	{
		printf("no error returned value = 0 \n");
	}
	else if(val==1)
	{
		printf("The PID number passed was not found\n" );

	}
	else
	{
		printf("returned value= %ld\n use $dmesg to see kernel log", val);
		printf("error Generated: %s\n", strerror((int)val));
	}
	return 0;
}


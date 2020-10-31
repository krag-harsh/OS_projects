/*HARSH KUMAR AGARWAL
2019423*/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/errno.h>

asmlinkage long sys_rtnice(int pid, long rtval) 
{
	printk("passed values:\npid : %d \nrtval : %ld\n",pid,rtval);

	struct task_struct *task;
	int flag=0;
	unsigned long long rtvalstore=rtval*1000000000;

	if (rtval < 0 || pid<0 || pid>32768)
		return -EINVAL;

	for_each_process(task) 
	{
		if (task->pid == pid) 
		{
			flag = 1;
			task->se.rtnice = rtvalstore;
			printk("rtnice value changed to: %ld\n", rtvalstore);
			break;
		}
	}

	if (flag == 0) 
	{
		printk("The process was not found with the given PID number");
		return -ESRCH;
	}

	printk("\nat the end of the rtnice code\n");
	return 0;
}


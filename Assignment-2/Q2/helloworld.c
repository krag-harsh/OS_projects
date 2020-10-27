#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/module.h>
#include <linux/unistd.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/string.h>

//asmlinkage long __x64_sys_hello(int pidno, char *filename)
SYSCALL_DEFINE2(hello, int, pidno, char __user *, filename)
{

    printk("Hello world1\n");
    printk("value access of pid first time = %d\n",pidno);
    int len= strlen(filename);
    len++;

    //int pidno=1;
    if (pidno <= 0 || pidno > 32768)
		return -EINVAL;

	struct task_struct *task;
	int flag = 0;


	struct file *file;
	loff_t pos = 0;
	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);
	char buffer[2000];

	char buffilename[256];
	copy_from_user(buffilename,filename,len);
	printk("next line will create file using filename passed %s\n",buffilename);
	file = filp_open(buffilename, O_WRONLY|O_CREAT, 0644);


	for_each_process(task)
	{
		if (pidno==(task->pid))
		{
			flag = 1;
			printk("\nPROCESS: %s\n PID_NUMBER: %ld\n \
					  PROCESS STATE: %ld\n PRIORITY: %ld\n RT_PRIORITY: %ld\n",
					  task->comm, (long)task_pid_nr(task), \
					  (long)task->state, (long)task->prio, \
					  (long)task->rt_priority);



			void *outputfile;
			sprintf(buffer, "\nProcess: %s\n \
				PID_NUMBER: %ld\n PROCESS STATE: %ld\n \
				PRIORITY: %ld\n RT_PRIORITY: %ld\n",
				task->comm, (long)task_pid_nr(task), \
				(long)task->state, (long)task->prio, \
				(long)task->rt_priority);

			outputfile = buffer;
			if (file)
			{	
				vfs_write(file, outputfile, strlen(buffer), &pos);
				filp_close(file,NULL);
				printk("\ninside if(file)\n");
			}
			else
				return -ENOENT;
			
		}
	}
	set_fs(old_fs);

	printk("GOOD JOB");

	if(flag==0)
		return 1;

    return 0;
}


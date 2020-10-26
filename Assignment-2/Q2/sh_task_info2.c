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
//#include "task_info.h"

asmlinkage long __x64_sys_sh_task_info(int pidno, char *filename)
{
	//pid can be max 2^15 check using $cat /proc/sys/kernel/pid.max
	if (pidno <= 0 || pidno > 32768)
		return -EINVAL;

	struct task_struct *task;
	int flag = 0;

	struct file *file;
	loff_t pos = 0;
	//int fd;
	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);

	char buffer[2000];

	//fd = sys_open(filename, O_WRONLY|O_CREAT, 0644);
	file = filp_open(filename, O_WRONLY|O_CREAT, 0644);

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

			char *outputfile;

			sprintf(buffer, "\nProcess: %s\n \
				PID_NUMBER: %ld\n PROCESS STATE: %ld\n \
				PRIORITY: %ld\n RT_PRIORITY: %ld\n",
				task->comm, (long)task_pid_nr(task), \
				(long)task->state, (long)task->prio, \
				(long)task->rt_priority);

			outputfile = buffer;

			// check if able to create file
			if (file)
			{
				//sys_write(fd, buffer, strlen(buffer));
				//file = fget(fd);

				// if (file)
				// {
				vfs_write(file, buffer, strlen(buffer), &pos);
				// fput(file);
				// }
				//sys_close(fd);
				filp_close(file,NULL);
			}
			else
				return -ENOENT;

		}
	}

	set_fs(old_fs);


	// pid number given did not exist does not exist
	if (flag==0)
		return -ESRCH;
	return 0;
}
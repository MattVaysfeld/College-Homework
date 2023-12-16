#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>

static int hello_init(void)
	{
		printk(KERN_ALERT "Hello, world from Matthew(10450114)\n");
		return 0;
	}
static void hello_exit(void)
	{
		printk(KERN_ALERT "pid : %d\n",current->pid);
		printk(KERN_ALERT "name : %s\n",current->comm);
	}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL");
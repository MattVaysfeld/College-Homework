/*
 * main.c -- the bare scull char module
 *
 * Copyright (C) 2001 Alessandro Rubini and Jonathan Corbet
 * Copyright (C) 2001 O'Reilly & Associates
 *
 * The source code in this file can be freely used, adapted,
 * and redistributed in source or binary form, so long as an
 * acknowledgment appears in derived source files.  The citation
 * should list that the code comes from the book "Linux Device
 * Drivers" by Alessandro Rubini and Jonathan Corbet, published
 * by O'Reilly & Associates.   No warranty is attached;
 * we cannot take responsibility for errors or fitness for use.
 *
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/cdev.h>

#include <linux/uaccess.h>	/* copy_*_user */

#include <linux/mutex.h>        /*mutex include*/

#include "scull.h"		/* local definitions */
#include "access_ok_version.h"


/*
 * Our parameters which can be set at load time.
 */

static int scull_major =   SCULL_MAJOR;
static int scull_minor =   0;
static int scull_quantum = SCULL_QUANTUM;

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_quantum, int, S_IRUGO);

MODULE_AUTHOR("Wonderful student of CS-492");
MODULE_LICENSE("Dual BSD/GPL");

static struct cdev scull_cdev;		/* Char device structure		*/


/* Linked List stuff */

/*Creates the node data structure*/
struct node{
	pid_t pid,tgid;
	struct list_head head;
};

/* Initialize LinkedList */
static LIST_HEAD(mylinkedlist);

/* Initialize Mutex */
static DEFINE_MUTEX(cache_lock);

/*
 * Open and close
 */

static int scull_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "scull open\n");
	return 0;          /* success */
}

static int scull_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "scull close\n");
	return 0;
}

/*
 * The ioctl() implementation
 */

static long scull_ioctl(struct file *filp, unsigned int cmd,
		unsigned long arg)
{

	int err = 0, tmp;
	int retval = 0;

	/* Declare things */
	struct task_info tmpInfo;
	struct node *tmpNode;
	struct list_head *i;
	int flag;

	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	 */
	if (_IOC_TYPE(cmd) != SCULL_IOC_MAGIC) return -ENOTTY;
	if (_IOC_NR(cmd) > SCULL_IOC_MAXNR) return -ENOTTY;

	/*
	 * the direction is a bitmask, and VERIFY_WRITE catches R/W
	 * transfers. `Type' is user-oriented, while
	 * access_ok is kernel-oriented, so the concept of "read" and
	 * "write" is reversed
	 */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok_wrapper(VERIFY_WRITE, (void __user *)arg,
				_IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok_wrapper(VERIFY_READ, (void __user *)arg,
				_IOC_SIZE(cmd));
	if (err) return -EFAULT;

	switch(cmd) {

	case SCULL_IOCRESET:
		scull_quantum = SCULL_QUANTUM;
		break;

	case SCULL_IOCSQUANTUM: /* Set: arg points to the value */
		retval = __get_user(scull_quantum, (int __user *)arg);
		break;

	case SCULL_IOCTQUANTUM: /* Tell: arg is the value */
		scull_quantum = arg;
		break;

	case SCULL_IOCGQUANTUM: /* Get: arg is pointer to result */
		retval = __put_user(scull_quantum, (int __user *)arg);
		break;

	case SCULL_IOCQQUANTUM: /* Query: return it (it's positive) */
		return scull_quantum;

	case SCULL_IOCXQUANTUM: /* eXchange: use arg as pointer */
		tmp = scull_quantum;
		retval = __get_user(scull_quantum, (int __user *)arg);
		if (retval == 0)
			retval = __put_user(tmp, (int __user *)arg);
		break;

	case SCULL_IOCHQUANTUM: /* sHift: like Tell + Query */
		tmp = scull_quantum;
		scull_quantum = arg;
		return tmp;

	case SCULL_IOCIQUANTUM: /* Info: Gets the task_info struct*/
		/*flag is false*/
		flag = 0;

		/* Allocate memory for node and check if it worked*/
		if(!(tmpNode = kmalloc(sizeof(struct node),GFP_KERNEL))){
			printk(KERN_ALERT "Malloc did not work");
		}
		else{
		/*If memory was allocated we can add the node*/
		mutex_lock(&cache_lock); /*lock mutex before you access linked_list*/
		list_for_each(i,&mylinkedlist){ /* Checks if the pid and tgid are already in the list*/
			struct node *obj = list_entry(i,struct node,head);
			if(obj->pid == current->pid && obj->tgid == current->tgid){
				flag = 1;
			}
		}
		if(flag == 0){
			/*If the pid and tgid are not in the list we can add the node using add_tail*/
			tmpNode->pid = current->pid;
			tmpNode->tgid = current->tgid;
			list_add_tail(&tmpNode->head,&mylinkedlist);
		}
		mutex_unlock(&cache_lock); /*unlock mutex after youre done accessing linked_list*/

		}

		/*Getting the info struct*/
		tmpInfo = (struct task_info){
				.state= current->state,
				.stack = current->stack,
				.cpu = current->cpu,
				.prio = current->prio,
				.static_prio = current->static_prio,
				.normal_prio = current->normal_prio,
				.rt_priority = current->rt_priority,
				.pid = current->pid,
				.tgid = current->tgid,
				.nvcsw = current->nvcsw,
				.nivcsw = current->nivcsw };

		/*copy_to_user the info struct and set as return value*/
		retval=copy_to_user((struct top_struct __user *)arg, &tmpInfo, sizeof(struct task_info));
		break;


	default:  /* redundant, as cmd was checked against MAXNR */
		return -ENOTTY;
	}
	return retval;

}


struct file_operations scull_fops = {
	.owner =    THIS_MODULE,
	.unlocked_ioctl = scull_ioctl,
	.open =     scull_open,
	.release =  scull_release,
};

/*
 * Finally, the module stuff
 */

/*
 * The cleanup function is used to handle initialization failures as well.
 * Thefore, it must be careful to work correctly even if some of the items
 * have not been initialized
 */
void scull_cleanup_module(void)
{
	/*Declare things*/
	int counter = 1;
	struct list_head *i;
	struct list_head *n;
	dev_t devno = MKDEV(scull_major, scull_minor);

	/* Get rid of the char dev entry */
	cdev_del(&scull_cdev);

	/* cleanup_module is never called if registering failed */
	unregister_chrdev_region(devno, 1);

	/*Print All the PIDS and TGID*/
	/*Also delete each node from the list and free memory*/
	list_for_each_safe(i,n,&mylinkedlist){
		struct node *obj = list_entry(i,struct node,head);
		printk(KERN_INFO "Task %d: PID: %ld, TGID: %ld\n",counter,(long)obj->pid,(long) obj->tgid);
		counter++;
		list_del(i);
		kfree(obj);
	};
}


int scull_init_module(void)
{
	int result;
	dev_t dev = 0;

	/*
	 * Get a range of minor numbers to work with, asking for a dynamic
	 * major unless directed otherwise at load time.
	 */
	if (scull_major) {
		dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev, 1, "scull");
	} else {
		result = alloc_chrdev_region(&dev, scull_minor, 1, "scull");
		scull_major = MAJOR(dev);
	}
	if (result < 0) {
		printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
		return result;
	}

	cdev_init(&scull_cdev, &scull_fops);
	scull_cdev.owner = THIS_MODULE;
	result = cdev_add (&scull_cdev, dev, 1);
	/* Fail gracefully if need be */
	if (result) {
		printk(KERN_NOTICE "Error %d adding scull character device", result);
		goto fail;
	}

	return 0; /* succeed */

  fail:
	scull_cleanup_module();
	return result;
}

module_init(scull_init_module);
module_exit(scull_cleanup_module);

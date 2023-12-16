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
#include <linux/semaphore.h>  /*semaphores*/

#include <linux/uaccess.h>	/* copy_*_user */

#include "scull.h"		/* local definitions */
#include "access_ok_version.h"

/*
 * Our parameters which can be set at load time.
 */

static int scull_major =   SCULL_MAJOR;
static int scull_minor =   0;
static int scull_fifo_elemsz = SCULL_FIFO_ELEMSZ_DEFAULT; /* SIZE */
static int scull_fifo_size   = SCULL_FIFO_SIZE_DEFAULT; /* N */

module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_fifo_size, int, S_IRUGO);
module_param(scull_fifo_elemsz, int, S_IRUGO);

MODULE_AUTHOR("Wonderful student of CS-492");
MODULE_LICENSE("Dual BSD/GPL");

static struct cdev scull_cdev;		/* Char device structure*/

char *queue;  /* pointer of memory allocated*/
char *start;
char *end;

struct semaphore seme;
struct semaphore semf;
static DEFINE_MUTEX(mut);



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
	return 0;          /* success */
}

/*
 * Read and Write
 */
static ssize_t scull_read(struct file *filp, char __user *buf, size_t count,
                loff_t *f_pos)
{
	size_t size;
	size_t r_size;

	//down(full)
	if(down_interruptible(&semf) == -EINTR){
		return -1;
	}
	//lock(mux)
	if(mutex_lock_interruptible(&mut) == -EINTR){
		up(&semf);
		return -1;
	}
	/* Figure out if were using count or the size of the block*/
	size = (size_t) *start;
	if(size < count){
		r_size = size;
	}
	else{
		r_size = count;
	}
	/*Move up pointer to go past len*/
	start = start + sizeof(size_t);

	/* Copy the bytes from the start to buffer*/
	if((__copy_to_user(buf,start,r_size)) > 0){
		printk(KERN_INFO "copying to buffer failed");
	}

	/*update start*/
	start = start + scull_fifo_elemsz;

	
	/*check if out of bounds*/
	/* address of start >= (address of queue + size of queue)*/
	if(start >= (queue + (scull_fifo_size * (sizeof(unsigned int) + scull_fifo_elemsz)))){
		start = queue;
	}

	//unlock(mux)
	mutex_unlock(&mut);
	//up(empty)
	up(&seme);

	printk(KERN_INFO "scull read\n");
	return r_size;
}


static ssize_t scull_write(struct file *filp, const char __user *buf, size_t count,
		loff_t *f_pos)
{


	size_t r_size;
	
	//down(empty)
	if(down_interruptible(&seme) == -EINTR){
		return -1;
	}
	//lock(mux)
	if(mutex_lock_interruptible(&mut) == -EINTR){
		up(&seme);
		return -1;
	}
	/* Figure out if were using count or the size of the block*/
	if(scull_fifo_elemsz < count){
		r_size = scull_fifo_elemsz;
	}
	else{
		r_size = count;
	}
	
	/* Store what the size is*/
	*end = r_size; 
	/*Move up pointer to go past len*/
	end = end + sizeof(size_t);
	
	/* Copy the bytes from the start to buffer*/
	if((__copy_from_user(end,buf,r_size)) > 0){
		printk(KERN_INFO "copying from buffer failed");
	}
	
	
	/*update end*/
	end = end + scull_fifo_elemsz;

	/*check if out of bounds*/
	/* address of end >= (address of queue + size of queue)*/
	if(end >= (queue + (scull_fifo_size * (sizeof(unsigned int) + scull_fifo_elemsz)))){
		end = queue;
	}

	//unlock(mux)
	mutex_unlock(&mut);
	//up(full)
	up(&semf);

	printk(KERN_INFO "scull write\n");
	return r_size; 
}

/*
 * The ioctl() implementation
 */

static long scull_ioctl(struct file *filp, unsigned int cmd,
		unsigned long arg)
{

	int err = 0;
	int retval = 0;
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
	case SCULL_IOCGETELEMSZ:
		return scull_fifo_elemsz;

	default:  /* redundant, as cmd was checked against MAXNR */
		return -ENOTTY;
	}
	return retval;

}


struct file_operations scull_fops = {
	.owner 		= THIS_MODULE,
	.unlocked_ioctl = scull_ioctl,
	.open 		= scull_open,
	.release	= scull_release,
	.read 		= scull_read,
	.write 		= scull_write,
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
	dev_t devno = MKDEV(scull_major, scull_minor);

	/* Free FIFO safely */
	kfree(queue);

	/* Get rid of the char dev entry */
	cdev_del(&scull_cdev);

	/* cleanup_module is never called if registering failed */
	unregister_chrdev_region(devno, 1);
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

	/* Allocate FIFO correctly */

	queue = kzalloc(scull_fifo_size * (sizeof(unsigned int) + scull_fifo_elemsz), GFP_KERNEL);
	if(!queue){
		printk(KERN_NOTICE "Error allocating memory");
		goto fail;
	}
	start = queue;
	end = queue;
	printk(KERN_INFO "scull: FIFO SIZE=%u, ELEMSZ=%u\n", scull_fifo_size,
			scull_fifo_elemsz);
	sema_init(&seme,scull_fifo_size);
	sema_init(&semf,0);

	return 0; /* succeed */

  fail:
	scull_cleanup_module();
	return result;
}

module_init(scull_init_module);
module_exit(scull_cleanup_module);

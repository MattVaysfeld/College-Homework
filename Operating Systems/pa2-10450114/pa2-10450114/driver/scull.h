/*
 * scull.h -- definitions for the char module
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
 * $Id: scull.h,v 1.15 2004/11/04 17:51:18 rubini Exp $
 */

#ifndef _SCULL_H_
#define _SCULL_H_

#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */

#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0   /* dynamic major by default */
#endif

/*
 * Task Struct
 */

struct task_info{long state; 
void *stack; 
unsigned int cpu; 
int prio;
int static_prio;
int normal_prio;
unsigned int rt_priority;
pid_t pid;
pid_t tgid;
unsigned long nvcsw;
unsigned long nivcsw;};

/*
 * SCULL_QUANTUM
 */
#ifndef SCULL_QUANTUM
#define SCULL_QUANTUM 4000
#endif


/*
 * Ioctl definitions
 */

/* Use 'k' as magic number */
#define SCULL_IOC_MAGIC  'k'

#define SCULL_IOCRESET    _IO(SCULL_IOC_MAGIC, 0)

/*
 * S means "Set" through a ptr,
 * T means "Tell" directly with the argument value
 * G means "Get": reply by setting through a pointer
 * Q means "Query": response is on the return value
 * X means "eXchange": switch G and S atomically
 * H means "sHift": switch T and Q atomically
 * i means "info" : gets the info task_struct
 */
#define SCULL_IOCSQUANTUM _IOW(SCULL_IOC_MAGIC,  1, int)
#define SCULL_IOCTQUANTUM _IO(SCULL_IOC_MAGIC,   2)
#define SCULL_IOCGQUANTUM _IOR(SCULL_IOC_MAGIC,  3, int)
#define SCULL_IOCQQUANTUM _IO(SCULL_IOC_MAGIC,   4)
#define SCULL_IOCXQUANTUM _IOWR(SCULL_IOC_MAGIC, 5, int)
#define SCULL_IOCHQUANTUM _IO(SCULL_IOC_MAGIC,   6)
#define SCULL_IOCIQUANTUM _IOR(SCULL_IOC_MAGIC, 7, struct task_info)

/* ... more to come */

#define SCULL_IOC_MAXNR 7

#endif /* _SCULL_H_ */

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
 * SCULL_FIFO_SIZE_DEFAULT
 */
#ifndef SCULL_FIFO_SIZE_DEFAULT
#define SCULL_FIFO_SIZE_DEFAULT 32
#endif

/*
 * SCULL_FIFO_NOELEM_DEFAULT
 */
#ifndef SCULL_FIFO_ELEMSZ_DEFAULT
#define SCULL_FIFO_ELEMSZ_DEFAULT 256
#endif



/*
 * Ioctl definitions
 */

/* Use 'k' as magic number */
#define SCULL_IOC_MAGIC  'k'
/* Please use a different 8-bit number in your code */

#define SCULL_IOCRESET    _IO(SCULL_IOC_MAGIC, 0)

/*
 * IOCTLs
 * GETELEMSZ - Get Element Size
 * SETSIZE - Set FIFO size (# of elements) (bonus)
 */
#define SCULL_IOCGETELEMSZ _IO(SCULL_IOC_MAGIC,  1)
#define SCULL_IOCSETSIZE   _IO(SCULL_IOC_MAGIC,  2)

#define SCULL_IOC_MAXNR 2

#endif /* _SCULL_H_ */

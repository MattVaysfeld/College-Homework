#ifndef _DEBUG_H_
#define _DEBUG_H_

/*
 * Macros to help debugging
 */

#undef PDEBUG             /* undef it, just in case */
#ifdef SCULL_DEBUG
#  ifdef __KERNEL__
     /* This one if debugging is on, and kernel space */
#    define PDDEBUG(fmt, args...) printk( KERN_DEBUG "scull: " fmt, ## args)
#    define PDEBUG(fmt, args...) printk( KERN_INFO  "scull: " fmt, ## args)
#  else
     /* This one for user space */
#    define PDDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDDEBUG(fmt, args...) /* not debugging: nothing */
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

#endif

#include <linux/syscalls.h>


SYSCALL_DEFINE1(Matthew_syscall, char __user *, s )
{
int x=0, count = 0;
int len;
char buff[128];
if((len = strlen_user(s)) == 0){
 return -1;
}
if (strncpy_from_user(buff, s, len) == -EFAULT){
	 return -1;
}

if(s == NULL || len > 32){
	return -1;
}
 
printk(KERN_ALERT "before: %s\n", buff);
 for(x = 0; x < len; x++){
        if(buff[x] == 'a' || buff[x] == 'e' || buff[x] == 'i' || buff[x] == 'o' || buff[x] == 'u' || buff[x] == 'y'){
           	buff[x] = 'X';
		count++;
        }
    } 
if(copy_to_user(s,buff,len)){
 	return -1;
}
printk(KERN_ALERT "after: %s\n",buff);

return count;
}

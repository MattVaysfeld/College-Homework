#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

long sys_call(char* s){
	return syscall(548,s);
}
int main(){
	char s1[64] = "Hello my name is Matthew and I do programming hello my name";
	char s2[32] = "Hello";
	long ans1;
	long ans2;
	printf("String1 given: %s\n",s1);
	ans1 = sys_call(s1);
	printf("String1 after syscall: %s\n",s1);
	printf("Return value for String1: %d\n",ans1);
	printf("String2 given: %s\n",s2);
	ans2 = sys_call(s2);
	printf("String2 after syscall: %s\n",s2);
	printf("Return value for String2: %d\n",ans2);
	return 0;
}

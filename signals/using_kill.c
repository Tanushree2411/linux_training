#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{
	int s,sig,s1;
	pid_t pid;
	if (argc != 2)
		//printf("%s sig-num pid\n", argv[0]);
		raise(15); //if not given the signum , it will termiate the processes with the same group id 
	sig = atoi(argv[1]);//signum
	pid = getpid();
	s = kill(pid, sig);//pid
	if (sig != 0) {
		if (s == -1)
			perror("kill");
	} else { /* Null signal: process existence check */
		if (s == 0) {
			printf("Process exists and we can send it a signal\n");
		} else {
			if (errno == EPERM)
				printf("Process exists, but we don't have "
						"permission to send it a signal\n");
			else if (errno == ESRCH)
				printf("Process does not exist\n");
			else
				perror("kill");
		}
	}
	exit(1);
}

#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	sigset_t blockSet, prevMask;
	/* Initialize a signal set to contain SIGINT */
	sigemptyset(&blockSet);
	sigaddset(&blockSet, SIGINT);
	/* Block SIGINT, save previous signal mask */
	if (sigprocmask(SIG_BLOCK, &blockSet, &prevMask) == -1)
		perror("sigprocmask1");
//	sleep(2);
	printf("masking done\n");
	for(int i=0;i<10;i++)
	{
		
		sleep(2);
		printf("%d",i);
	//	sleep(2);
	}

	/* ... Code that should not be interrupted by SIGINT ... */
	/* Restore previous signal mask, unblocking SIGINT */
	printf("doing unmaakinf\n");
	if (sigprocmask(SIG_SETMASK, &prevMask, NULL) == -1)
		perror("sigprocmask2");
//	printf("unmasking done\n");

}

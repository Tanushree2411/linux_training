#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int numSigs, sig, j;
	pid_t pid;
	pid=getpid();
	if (argc < 3 || strcmp(argv[1], "--help") == 0)
		printf("%s pid num-sigs sig-num [sig-num-2]\n", argv[0]);
		// pid = getLong(argv[1], 0, "PID");
	 numSigs = atoi(argv[1]);//num_signal
	 sig = atoi(argv[2]);//signum
	 /* Send signals to receiver */
	 printf("%s: sending signal %d to process %ld %d times\n",
			 argv[0], sig, (long) pid, numSigs);
	 for (j = 0; j < numSigs; j++)
		 if (kill(pid, sig) == -1)
			 perror("kill");
	 /* If a fourth command-line argument was specified, send that signal */
	 if (argc > 3)
		 if (kill(pid, atoi(argv[3])) == -1) //other signal
			 perror("kill");
	 printf("%s: exiting\n", argv[0]);
	 exit(1);
}

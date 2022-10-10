#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int
main(int argc, char *argv[])
{
 int numChildren, j;
 pid_t childPid;
 //if (argc > 1 && strcmp(argv[1], "--help") == 0)
 //usageErr("%s [num-children]\n", argv[0]);
 numChildren = 1000;
// setbuf(stdout, NULL); 
 /* Make stdout unbuffered */
 for (j = 0; j < numChildren; j++) {
 switch (childPid = vfork()) {
 case -1:
         printf("error");
 //errExit("fork");
 case 0:
 printf("%d child\n", j);
 _exit(0);
 default:
 printf("%d parent\n", j);
 wait(NULL); /* Wait for child to terminate */
 break;
 }
 }
 exit(0);
}
  

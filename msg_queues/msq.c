//displaying all messgae queus n its info
#include <sys/types.h>
#include <sys/msg.h>
#include <errno.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
 int maxind, ind, msqid;
 struct msqid_ds ds;
 struct msginfo msginfo;
 /* Obtain size of kernel 'entries' array */
 maxind = msgctl(0, MSG_INFO, (struct msqid_ds *) &msginfo);
 if (maxind == -1)
	 printf("msgctl-MSG_INFO not there");
 printf("maxind: %d\n\n", maxind);
 printf("index   id    key    messages\n");
 /* Retrieve and display information from each element of 'entries' array */
 for (ind = 0; ind <= maxind; ind++) {
 msqid = msgctl(ind, MSG_STAT, &ds);
 if (msqid == -1) {
 if (errno != EINVAL && errno != EACCES)
 printf("msgctl-MSG_STAT unexpected error\n"); /* Unexpected error */
 continue; /* Ignore this item */
 }
 printf("%4d %8d  0x%08lx %7ld\n", ind, msqid,
 (unsigned long) ds.msg_perm.__key, (long) ds.msg_qnum);
 }
 exit(1);
}

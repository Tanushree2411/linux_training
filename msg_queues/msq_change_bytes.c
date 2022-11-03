//: Changing the msg_qbytes setting of a System V message queue
#include <sys/types.h>
#include <sys/msg.h>
#include "main_headers.h"

int main(int argc, char *argv[])
{
 struct msqid_ds ds;
 int msqid;
 if (argc != 3 || strcmp(argv[1], "--help") == 0)
 	printf("%s msqid max-bytes\n", argv[0]);
 /* Retrieve copy of associated data structure from kernel */
 msqid = atoi(argv[1]);
 if (msgctl(msqid, IPC_STAT, &ds) == -1)
 	printf("msgctl error in ipc_stat");
 ds.msg_qbytes = atoi(argv[2]);
 /* Update associated data structure in kernel */
 if (msgctl(msqid, IPC_SET, &ds) == -1)
 	printf("error in msgctl ipc_set\n");
 exit(1);
}


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "main_headers.h"

#define SERVER_FIFO "/tmp/seqnum_sv"
#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_cl.%ld"
#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20)

struct request { /* Request (client --> server) */
 pid_t pid; /* PID of client */
 int seqLen; /* Length of desired sequence */
};

struct response { /* Response (server --> client) */
 int seqNum; /* Start of sequence */
};

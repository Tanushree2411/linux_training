#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<errno.h>
#define BUF_SIZE 10 /* Maximum size of messages exchanged between client to server */
#define SV_SOCK_PATH "/tmp/ud_ucase"
#include<stdlib.h>
int main(int argc, char *argv[])
{
	struct sockaddr_un svaddr, claddr;
	int sfd, j;
	size_t msgLen;
	ssize_t numBytes;
	char resp[BUF_SIZE];
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		printf("%s msg...\n", argv[0]);
	/* Create client socket; bind to unique pathname (based on PID) */
	sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sfd == -1)
		perror("socket");
	memset(&claddr, 0, sizeof(struct sockaddr_un));
	claddr.sun_family = AF_UNIX;
	snprintf(claddr.sun_path, sizeof(claddr.sun_path),
			"/tmp/ud_ucase_cl.%ld", (long) getpid());
	if (bind(sfd, (struct sockaddr *) &claddr, sizeof(struct sockaddr_un)) == -1)
		perror("bind");
	/* Construct address of server */
	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);
	/* Send messages to server; echo responses on stdout */
	for (j = 1; j < argc; j++) {
		msgLen = strlen(argv[j]); /* May be longer than BUF_SIZE */
		if (sendto(sfd, argv[j], msgLen, 0, (struct sockaddr *) &svaddr,
					sizeof(struct sockaddr_un)) != msgLen)
			perror("sendto");
		numBytes = recvfrom(sfd, resp, BUF_SIZE, 0, NULL, NULL);
		if (numBytes == -1)
			perror("recvfrom");
		printf("Response %d: %.*s\n", j, (int) numBytes, resp);
	}
	remove(claddr.sun_path); /* Remove client socket pathname */
	exit(1);
}

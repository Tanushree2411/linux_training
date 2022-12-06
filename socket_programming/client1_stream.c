#include<stdio.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 100
int main(int argc, char *argv[])
{
	struct sockaddr_un addr;
	int sfd;
	ssize_t numRead;
	char buf[BUF_SIZE];
	sfd = socket(AF_UNIX, SOCK_STREAM, 0); /* Create client socket */
	if (sfd == -1)
		perror("socket");
	/* Construct server address, and make the connection */
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
	if (connect(sfd, (struct sockaddr *) &addr,
				sizeof(struct sockaddr_un)) == -1)
		perror("connect");
	/* Copy stdin to socket */
	while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
		if (write(sfd, buf, numRead) != numRead)
			printf("partial/failed write\n");
	if (numRead == -1)
		perror("read");
	exit(1); /* Closes our socket; server sees EOF */
}

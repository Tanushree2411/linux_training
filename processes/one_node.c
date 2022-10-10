#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>

//Linked list add
struct Node{
                int data;
                struct Node* next;
};


int main(void)
{
	int i,fd[2],nbytes;
	pid_t childpid;
	char string[]="Linux Kernel Technology\n";
	char readbuffer[50];
	struct Node *mynode = malloc(sizeof(struct Node));
	struct Node *rnode = malloc(sizeof(struct Node));

	mynode->data=10;
	pipe(fd);

	if((childpid = fork()) == -1){
		perror("fork");
		exit(1);
	}
	if(childpid == 0){
		/* Child process closes up input side of pipe */
		close(fd[0]);
		/* Send "string" through the output side of pipe */
		write(fd[1], mynode, sizeof(mynode)); 
		//exit(0);
	}
	else
	{
		/* Parent process closes up output side of pipe */
		close(fd[1]);
		/* Read in a string from the pipe */
		nbytes = read(fd[0], rnode, sizeof(rnode));
		if(nbytes != 0)
		{
			printf("node->data=%d\n", rnode->data);
			//printf("Received string: %s", readbuffer);
		}

	}
	return 0;
}

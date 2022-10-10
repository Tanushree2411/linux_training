#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
//Linked list add
struct Node{
                int data;
                struct Node* next;
};

struct Node* beginsert();

int main(void)
{
        int i,fd[2],nbytes;
        pid_t childpid;
        char string[]="Linux Kernel Technology\n";
        char readbuffer[50];
        struct Node *mynode = malloc(sizeof(struct Node));
        struct Node *rnode = malloc(sizeof(struct Node));

//        mynode->data=10;
//	mynode->next=NULL;
        pipe(fd);
//	static int ei;
	if((childpid = fork()) == -1){
		perror("fork");
		exit(1);
	}
	if(childpid == 0){
		/* Child process closes up input side of pipe */
		close(fd[0]);
		//	ei++;
		/* Send "string" through the output side of pipe */
		for(int i = 0; i < 3;i++){

			mynode=beginsert();
			write(fd[1], mynode, sizeof(mynode));
			// exit(0);
		}
		close(fd[1]);
	}
	else
	{

		/* Parent process closes up output side of pipe */


		close(fd[1]);
		//if (close(fd[0]) == -1)
		/* Read in a string from the pipe */
		for(;;)
		{
			nbytes = read(fd[0], rnode, sizeof(rnode));
			if(nbytes == -1)
				printf("error in read\n");
			if(nbytes == 0)
				break;


			if(nbytes >  0)
				//{
				//	sleep(1);
				printf("node->data=%d\n", rnode->data);
			//       printf("ei:%d\n", ei);

		}
		wait(NULL);
//		printf("Aavjoooooooooooo\n");

		}
	}	
	struct Node* beginsert(struct Node *mynode)

	{
		struct Node *ptr;
		int item;
		ptr = (struct Node *) malloc(sizeof(struct Node *));
		if(ptr == NULL)
		{
			printf("\nmemory not allocated");
			return 0;
		}
		else
		{
			printf("\nmemory allocated successfully\n");
			printf("\nEnter value\n");
			scanf("%d",&item);
			ptr->data = item;
			ptr->next = mynode;
			mynode = ptr;
			printf("\nNode inserted");
			return mynode;
		}

	}


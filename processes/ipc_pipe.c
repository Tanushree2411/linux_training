#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>


int main(void)
{
	int i,fd[2],nbytes;
	pid_t childpid;
	char string[]="Linux Kernel Technology\n";
	char readbuffer[50];
	pipe(fd);



	if((childpid = fork()) == -1){
		perror("fork");
		exit(1);
	}
	if(childpid == 0){
		/* Child process closes up input side of pipe */
		close(fd[0]);
		/* Send "string" through the output side of pipe */
		write(fd [1], string, (strlen(string)+1)); 
		exit(0);
	}
	else{
		/* Parent process closes up output side of pipe */
		close(fd[1]);
		/* Read in a string from the pipe */
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		for(i=0; i<=nbytes; i++){
			if(readbuffer[i] >= 'a' && readbuffer[i] <= 'z'){
				readbuffer[i] = readbuffer[i] - 32;}
			//printf("Received string: %s", readbuffer);
		}

	}
	printf("Received string: %s", readbuffer);
	return 0;
}
